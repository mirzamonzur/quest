/* 
 * File:   Lattice.cpp
 * Author: K M Masum Habib <khabib@ee.ucr.edu>
 * 
 * Created on April 7, 2013, 9:46 AM
 * 
 * Description: Lattice vector and lattice coordinates.
 * 
 */

#include "Lattice.h"

namespace qmicad{

/* Lattice coordinate */


LatticeCoordinate::LatticeCoordinate(int n1, int n2, int n3, const string &prefix)
    :Printable(" " + prefix), n1(n1), n2(n2), n3(n3)
{
}

LatticeCoordinate operator+ (LatticeCoordinate lhs, const LatticeCoordinate& rhs){
    lhs += rhs;
    return lhs;
}

LatticeCoordinate& LatticeCoordinate::operator+= (const LatticeCoordinate& rhs){
    
    n1 += rhs.n1;
    n2 += rhs.n2;
    n3 += rhs.n3;
    
    return *this;
}

LatticeCoordinate operator- (LatticeCoordinate lhs, const LatticeCoordinate& rhs){
    lhs -= rhs;
    return lhs;
}

LatticeCoordinate& LatticeCoordinate::operator-= (const LatticeCoordinate& rhs){
    
    n1 -= rhs.n1;
    n2 -= rhs.n2;
    n3 -= rhs.n3;
    
    return *this;
}

string LatticeCoordinate::toString() const{
    stringstream out;
    
    out << "[";
    out.width(3);
    out << n1; 
    out << ", ";
    out.width(3);
    out << n2; 
    out << ", ";
    out.width(3);
    out << n3;
    out << "]";

    return out.str();
}

/** 
 * Lattice vector.
 */
LatticeVector::LatticeVector(const string &prefix):
    Printable(" " + prefix)
{
    zeros();
}


void LatticeVector::zeros(){
    a1.zeros();
    a2.zeros();
    a3.zeros();    
}

LatticeVector operator+ (LatticeVector lhs, const LatticeVector& rhs){
    lhs += rhs;
    return lhs;
}

LatticeVector& LatticeVector::operator+= (const LatticeVector& rhs){
    
    a1 += rhs.a1;
    a2 += rhs.a2;
    a3 += rhs.a3;
    
    return *this;
}

LatticeVector operator- (LatticeVector lhs, const LatticeVector& rhs){
    lhs -= rhs;
    return lhs;
}

LatticeVector& LatticeVector::operator-= (const LatticeVector& rhs){
    
    a1 -= rhs.a1;
    a2 -= rhs.a2;
    a3 -= rhs.a3;
    
    return *this;
}


svec operator*(const LatticeVector &lv, const LatticeCoordinate& lc){
    svec sv = lv.a1*lc.n1 + lv.a2*lc.n2 + lv.a3*lc.n3;
    return sv;
}

string LatticeVector::toString() const{
        
    stringstream out;
    out.precision(4);
    out << " a1 = [" << std::fixed << a1(coord::X) << " " 
                     << std::fixed << a1(coord::Y) << " " 
                     << std::fixed << a1(coord::Z) << "]" << endl;
    out << " a2 = [" << std::fixed << a2(coord::X) << " " 
                     << std::fixed << a2(coord::Y) << " " 
                     << std::fixed << a2(coord::Z) << "]" << endl;
    out << " a3 = [" << std::fixed << a3(coord::X) << " " 
                     << std::fixed << a3(coord::Y) << " " 
                     << std::fixed << a3(coord::Z) << "]";
    
    return out.str();
}

}

