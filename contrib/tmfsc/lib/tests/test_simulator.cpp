/** Test cases for Segment class.
 *
 */

#include "simulator.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SimulatorTest
#include <boost/test/unit_test.hpp>

#include <iostream>

using namespace qmicad::tmfsc;
using namespace std;

BOOST_AUTO_TEST_CASE(basics)
{

    point A = {0, 0};    
    point B = {20, 0};    
    point C = {20, 20};    
    point D = {0, 20};    

    Device dev;
    dev.addPoint(A);
    dev.addPoint(B);
    dev.addPoint(C);
    dev.addPoint(D);
    dev.addPoint(A);

    dev.edgeType(1, Edge::EDGE_ABSORB);

    Simulator sim(dev);
    sim.setMaxNumTimeStep(100);

    point p = {10, 5};
    vector<point> pts;
    pts = sim.calcTraj(p, 0.0, 10, 0, 0.15);
    cout << " *** TRAJECTORY *** " << endl;
    for (int ip = 0; ip < pts.size(); ip += 1) {
        cout << "[" << ip << "]" << pts[ip] << endl;
    }





    
}


