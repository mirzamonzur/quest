/* 
 * File:   AtomicStruct.cpp
 * Author: K M Masum Habib <khabib@ee.ucr.edu>
 * 
 * Created on April 5, 2013, 1:27 PM
 * 
 * Description: The class Atoms encapsulates everything about the atoms present in
 * the device structure.
 * 
 */

#include "AtomicStruct.h"

namespace qmicad{
/* Default constructor */
AtomicStruct::AtomicStruct():mpt() {
    init();
}

// constructs from a GaussView gjf file and a periodic table
AtomicStruct::AtomicStruct(const string& gjfFileName, const ptable &periodicTable):
mpt(periodicTable){    
    init();
    importGjf(gjfFileName);
}

/* Construct from a GaussView gjf file */
AtomicStruct::AtomicStruct(const string& gjfFileName):mpt() {
    init();
    
    importGjf(gjfFileName);
}

/* Copy constructor */
AtomicStruct::AtomicStruct(const AtomicStruct& orig):
mlv(orig.mlv),
mia(orig.mia),
mpt(orig.mpt),
mXyz(orig.mXyz)
{
    mNa = orig.mNa;
    mNo = orig.mNo;
    mNe = orig.mNe;
}

/* Construct from coordinates */
AtomicStruct::AtomicStruct(const icol& atomId, const mat& coordinate, const lvec& lv):
mpt()
{
    if (atomId.n_rows != coordinate.n_rows){
        throw invalid_argument("In Atoms::Atoms(const icol& atomId, const mat& "
                "coordinate, const lvec& lv) number of rows of atomId and "
                "coordinate does not match");
    }
    
    mlv = lv;
    mia = atomId;
    mXyz = coordinate;

    mNa = mia.n_rows;
    mNo = computeNumOfOrbitals();
    mNe = computeNumOfElectrons();    
}

/* Construct from coordinates and a periodic table*/
AtomicStruct::AtomicStruct(const icol& atomId, const mat& coordinate, const lvec& lv,
const ptable& periodicTable):mpt(periodicTable){
    if (atomId.n_rows != coordinate.n_rows){
        throw invalid_argument("In Atoms::Atoms(const icol& atomId, const mat& "
                "coordinate, const lvec& lv) number of rows of atomId and "
                "coordinate does not match");
    }
    
    mlv = lv;
    mia = atomId;
    mXyz = coordinate;

    mNa = mia.n_rows;
    mNo = computeNumOfOrbitals();
    mNe = computeNumOfElectrons();    
}

AtomicStruct::AtomicStruct(double Lx, double Ly, double ax, double ay, const ptable& 
    periodicTable)
{
    init();
    genKpAtoms(Lx, Ly, ax, ay, periodicTable);
}

/* initializer */
void AtomicStruct::init(){
    mNa = 0;
    mNo = 0;
    mNe = 0;
    mia.clear();
    mXyz.clear();
    mlv.zeros();
}

/* Assignment operator: 
 * c = b; creates a copy of b and assigns it to c*/
AtomicStruct& AtomicStruct::operator= (AtomicStruct rhs){
    swap(*this, rhs);
    
    return *this;
}

/* Swaps two Atoms objects */
void swap(AtomicStruct& first, AtomicStruct& second){
    using std::swap;

    swap(first.mlv, second.mlv);
    swap(first.mia, second.mia);
    swap(first.mNa, second.mNa);
    swap(first.mNe, second.mNe);
    swap(first.mNo, second.mNo);
    swap(first.mpt, second.mpt);
    
    /* The swap function in armadillo probably has a bug
     * that prevents swapping a zero sized matrix
     */
    if (first.mXyz.empty() || second.mXyz.empty()){
        std::swap(first.mXyz, second.mXyz);
    }else{
        swap(first.mXyz, second.mXyz);
    }
    
}

/* Concatenation: atmi + atmj */
AtomicStruct operator+ (AtomicStruct atmi, const AtomicStruct& atmj){
    atmi += atmj;
    return atmi;
}

/* Concatenation: atmi += atmj */
AtomicStruct& AtomicStruct::operator+= (const AtomicStruct& atj){

    // update the periodic table
    for(int it = 0; it != atj.mpt.size(); ++it){
        // Update our table if we do not already have  
        // the atoms in atj;
        if (mpt.find(atj.mpt[it]) == -1){ // not found in our database
            mpt.add(atj.mpt[it]);     // insert it to our database
        }
    }
    
    // concatenate the atom id's and coordinates
    mia.insert_rows(mNa,atj.mia);
    mXyz.insert_rows(mNa,atj.mXyz);
    
    // add the lattice vectors
    mlv += atj.mlv;
    
    // add the number of atoms, orbitals and electrons
    mNa += atj.mNa;
    mNo += atj.mNo;
    mNe += atj.mNe;
    
    return *this;
}

/* Atoms - Lattice coordinate*/
AtomicStruct operator- (AtomicStruct atm, const lcoord& lc){
    atm -= lc;
    return atm;
};

/* Atoms -= Lattice coordinate*/
AtomicStruct& AtomicStruct::operator-= (const lcoord& lc){
    
    *this -= mlv.a1*lc.n1;
    *this -= mlv.a2*lc.n2;
    *this -= mlv.a3*lc.n3;
    
    return *this;
}

/* Atoms = Atoms - position vector */
AtomicStruct operator- (AtomicStruct atm, const svec& r){
    atm -= r;
    return atm;
};

/* Atoms -= position vector */
AtomicStruct& AtomicStruct::operator-= (const svec& rvec){
    
    mXyz.col(spacevec::X) -= rvec(spacevec::X);
    mXyz.col(spacevec::Y) -= rvec(spacevec::Y);
    mXyz.col(spacevec::Z) -= rvec(spacevec::Z);
    
    return *this;
}

/* Atoms + Lattice coordinate*/
AtomicStruct operator+ (AtomicStruct atm, const lcoord& lc){
    atm += lc;
    return atm;
};

/* Atoms += Lattice coordinate*/
AtomicStruct& AtomicStruct::operator+= (const lcoord& lc){
    
    *this += mlv.a1*lc.n1;
    *this += mlv.a2*lc.n2;
    *this += mlv.a3*lc.n3;
    
    return *this;
}

/* Atoms = Atoms + position vector */
AtomicStruct operator+ (AtomicStruct atm, const svec& r){
    atm += r;
    return atm;
};

/* Atoms += position vector */
AtomicStruct& AtomicStruct::operator+= (const svec& rvec){
    
    mXyz.col(spacevec::X) += rvec(spacevec::X);
    mXyz.col(spacevec::Y) += rvec(spacevec::Y);
    mXyz.col(spacevec::Z) += rvec(spacevec::Z);
    
    return *this;
}

/*
 * Callable operators to extract a subset of atoms whose atom indices are stored
 * in column vector.
 * @FIXME: these operators does not guarantee correct lattice vector.
 */
AtomicStruct AtomicStruct::operator ()(const ucol& index) const{
    
    //get only the atoms we are interested in
    icol atomId = mia.elem(index);   
    ucol cols;
    cols << spacevec::X << spacevec::Y << spacevec::Z;
    mat coordinate = mXyz(index,cols);        

    return AtomicStruct(atomId, coordinate, mlv, mpt);
}

/*
 * Callable operators to extract a subset of atoms defined by a span.
 * @FIXME: these operators does not guarantee correct lattice vector.
 */
AtomicStruct AtomicStruct::operator ()(span s) const{
    
    //get only the atoms we are interested in
    icol atomId = mia(s);   
    mat coordinate = mXyz(s,span::all); 

    return AtomicStruct(atomId, coordinate, mlv, mpt);
}

/*
 * Callable operators to extract a one atom with index i.
 * @FIXME: these operators does not guarantee correct lattice vector.
 */

AtomicStruct AtomicStruct::operator ()(uint i) const{
    
    ucol index(1);
    index(0) = i;
    return (*this)(index);
}

Atom AtomicStruct::AtomAt(uint i) const{
    return mpt[mia[i]];
}

/* Dump the data to the stream */
//ostream& operator << (ostream & out, const AtomicStruct &b){
//    out << b.toString();
//	return out;
//}

string AtomicStruct::toString() const{
    
    stringstream out;
    // write the file header
    out << "# hf/3-21g" << endl; // header command
    out << endl;
    out << "GRAPHENE" << endl;   // tittle
    out << endl;
    out << "0 1" << endl;        // charge spin
    
    // write atomic coordinates
    out.precision(4);
    out << std::fixed;
    for(int i=0; i < NumOfAtoms(); i++){
        out.width(3);
        out << Symbol(i);
        out.width(10); 
        out << std::fixed << X(i);
        out.width(10);
        out << Y(i);
        out.width(10);
        out << Z(i) << endl;
    }
    
    out << endl;
    
	return out.str();
}


void AtomicStruct::importGjf(const string& gjfFileName){
    string line;
    ifstream gjf (gjfFileName.c_str());        
    
    if(!gjf.is_open()){
        throw runtime_error("Failed to open file " + gjfFileName + ".");
    }
    
    // reset values
    init();
    
    bool inHeader = true;
    while(gjf.good()){
        getline(gjf, line);

        line = trim(line); 
        // Skip the comment, the command and the blank lines
        // and get the coordinates
        if(!inHeader && line.length() > 0 && line[0] != '#'
           && line[0] != '%' && line[0] != '\n'){
            
            stringstream ssline (line);
            string sym;
            double x, y, z;
            int ind;
            
            ssline >> sym >> x >> y >> z;

            ind = mpt.find(sym);
            if (ind > -1){
                
                mia.resize(mNa+1);
                mia(mNa) =  ind;
                
                row r(3);
                r << x << y << z;
                mXyz.insert_rows(mXyz.n_rows,r);
                
                mNo += mpt[ind].no;
                mNe += mpt[ind].ne;
                mNa++;
            }

        // If we find the line that contains "0 1" which is 
        // the spin and charge specification, then we are in the 
        // coordinate section of the gjf file.
        }else if(inHeader && isdigit(line[0])){ 
            inHeader = false;
        }        
    }
    
    if (mNa == 0){
        mia.reset();
        mXyz.reset();
        
        throw runtime_error(" No atoms found in " + gjfFileName + ".");;
    }
}

void AtomicStruct::exportGjf(const string& gjfFileName){
    
    ofstream gjf(gjfFileName.c_str());
    
    if (!gjf.is_open()){
        throw runtime_error(" Failed to open file " + gjfFileName + ".");
    }
        
    gjf << *this;
    gjf.close();
}

void AtomicStruct::genKpAtoms(uint nl, uint nw, double ax, double ay, 
        const ptable &periodicTable){
    
    double w = (nw-1)*ax;                  // width (in A)
    double l = (nl-1)*ay;                  // length  (in A)
    // create meshgrid of k.p atoms    
    MatGrid xy(-l/2, l/2, ax, -w/2, w/2, ay);
    
    // calculate x, y and z coordinates of the atoms
    mNa = xy.Nx()*xy.Ny();            // total number of atoms
    mXyz.set_size(mNa, 3);            // xyz coordinate of atoms
    mXyz.col(spacevec::X) = xy.X();
    mXyz.col(spacevec::Y) = xy.Y();
    mXyz.col(spacevec::Z).zeros();
    
    // prepare atomId list containing atomic number of a fake atom 'D'.
    mia.set_size(mNa);
    mpt = periodicTable;           // Copy the periodic table.
    mia.fill(mpt[0].ia);
    
    // lattice vector
    mlv.a1(spacevec::X) = xy.maxx()-xy.minx() + ax;
    mlv.a2(spacevec::Y) = xy.maxy()-xy.miny() + ay;  
    
    // calculate number of orbitals and electrons.
    mNo = computeNumOfOrbitals();
    mNe = computeNumOfElectrons();    
 
}

int AtomicStruct::computeNumOfOrbitals(){
    int numOrbitals = 0;
    for(int ia = 0; ia < mNa; ++ia){
        numOrbitals += mpt[mia[ia]].no; 
    }
    
    return numOrbitals;
}

int AtomicStruct::computeNumOfElectrons(){
    int numElectrons = 0;
    for(int ia = 0; ia < mNa; ++ia){
        numElectrons += mpt[mia[ia]].ne;       
    }
    
    return numElectrons;
}

void AtomicStruct::PeriodicTable(const ptable& periodicTable){
    mpt = periodicTable; 
    mNo = computeNumOfOrbitals();
    mNe = computeNumOfElectrons();
}

}

