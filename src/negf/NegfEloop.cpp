/* 
 * File:   NegfEloop.cpp
 * Author: K M Masum Habib<masum.habib@virginia.edu>
 *
 * Created on January 28, 2014, 7:20 PM
 */

#include "NegfEloop.h"
#include "NegfResult.h"

namespace qmicad{

NegfEloop::NegfEloop(const VecGrid &E, const CohRgfaParams &np, 
        const Workers &workers, bool isAscii): ParLoop(workers, E.N()), 
        mnp(np), mE(E), mIsAscii(isAscii), mbar("  NEGF: ",  E.N())
{   
}
    

void NegfEloop::prepare() {
    mWorkers.Comm().barrier();
    mbar.start();
}

void NegfEloop::preCompute(int il){
    double E = mE(il);
    mnegf = shared_ptr<CohRgfa>(new CohRgfa(mnp, E));
};

void NegfEloop::compute(int il){
    negf_result r;                       // pair of energy and result
    r.first = mE(il);                   // first => energy
    // Transmission
    if(mTE.isEnabled()){
        r.second = mnegf->TEop(mTE.N);  // second => T(E)
        mThisTE.push_back(r);  
    }
    // Current
    map<uint, vec_result>::iterator it;  // map of block # and vector of negf result
    for (it = mThisIop.begin(); it != mThisIop.end(); ++it){
        uint ib = it->first;
        r.second = mnegf->Iop(ib, mIop[ib].N); // r.second => Iop (E)
        it->second.push_back(r);           // it->second => vector of Iop()
    }
}

void NegfEloop::postCompute(int il){
    mnegf.reset();          // free up memory
    ++mbar;                 // Show feedback
}

void NegfEloop::collect(){
    // Update the progress bar.
    mWorkers.Comm().barrier();
    mbar.complete();
    
    // Gather transmission
    if(mTE.isEnabled()){
        gather(mThisTE, mTE);
    }

    // Gather current
    map<uint, vec_result>::iterator it;  // first => block #, second => vecresult.
    for (it = mThisIop.begin(); it != mThisIop.end(); ++it){
        uint ib = it->first;
        gather(it->second, mIop[ib]);
    }
}

void NegfEloop::gather(vec_result &thisR, NegfResultList &all){

    if(!mWorkers.IAmMaster()){    
        // slaves send their local data
        mpi::gather(mWorkers.Comm(), thisR, mWorkers.MasterId());

    // The master collects data        
    }else{
        // Collect T(E)
        vector<vector<negf_result> >gatheredR(mN);
        mpi::gather(mWorkers.Comm(), thisR, gatheredR, mWorkers.MasterId());
        
        // merge and store results on mTE list.
        vector<vector<negf_result> >::iterator it;
        for (it = gatheredR.begin(); it != gatheredR.end(); ++it){
            all.R.insert(all.R.end(), it->begin(), it->end());
        }
        // Sort the results based on energy.
        all.sort();
    }       
}

void NegfEloop::save(string fileName){
    if(mWorkers.IAmMaster()){
        // save to a file
        ofstream out;
        if(mIsAscii){
            out.open(fileName.c_str(), ostream::binary|ios::app);
        }else{
            out.open(fileName.c_str(), ios::app);
        }
        if (!out.is_open()){
            throw ios_base::failure(" NegfResult::saveTE(): Failed to open file " 
                    + fileName + ".");
        }
        
        // Transmission 
        if (mTE.isEnabled()){
            mTE.save(out);
        }
        
        // Current
        map<uint, NegfResultList>::iterator it;  // first => block #, second => NegfResultList.
        for (it = mIop.begin(); it != mIop.end(); ++it){
            it->second.save(out);
        }
    }
}

void NegfEloop::enableTE(uint N){
    mTE.tag = "TRANSMISSION";
    mTE.N = N;
}

void NegfEloop::enableI(uint ib, uint N){
    stringstream out;
    out << "CURRENT" << ib;
    mIop[ib] = NegfResultList(out.str(), N);
    mThisIop[ib] = vec_result();
}

}
