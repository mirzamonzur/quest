/* 
 * File:   geometry.hpp
 * Copyright (C) 2014  K M Masum Habib <masum.habib@gmail.com>
 *
 * Created on February 3, 2014, 1:45 PM
 */

#ifndef GEOMETRY_HPP
#define	GEOMETRY_HPP

#include "utils/std.hpp"
#include "utils/Printable.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

#include <vector>
#include <algorithm>

namespace maths{
namespace geometry{

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
using namespace utils::stds;
using utils::Printable;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef bg::model::ring<point> ring;
typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
typedef polygon::ring_type polyring;
typedef bg::strategy::within::franklin<point, point, double> stwithin;

/*
 * Simple Quadrilateral
 */
struct SimpleQuadrilateral: public Printable{
    point lb;
    point rb;
    point rt;
    point lt;

    SimpleQuadrilateral(const point &lb, const point &rb, const point &rt, 
    const point &lt, const string &prefix = ""):Printable(" " + prefix), 
        lb(lb), rb(rb), rt(rt), lt(lt){
        
        // Commented out since it is buggy
        // correct();
    }    
    
    // sort the points.
    // @TODO: Does not alway work. Fix bug. 
    void correct(){
        using std::sort;
        using std::vector;
        vector<point> p;
        p.push_back(lb);
        p.push_back(rb);
        p.push_back(rt);
        p.push_back(lt);
        
        sort(p.begin(), p.end(), OnRight());
        
        if (p[0].get<1>() < p[1].get<1>()){
            lb = p[0];
            lt = p[1];
        }else{
            lb = p[1];
            lt = p[0];            
        }
        
        if (p[2].get<1>() < p[3].get<1>()){
            rb = p[2];
            rt = p[3];
        }else{
            rb = p[3];
            rt = p[2];            
        }        
    }
    
    
    
    virtual string toString() const{
        stringstream out;
        out.precision(3);
        out << "(" << lb.get<0>() << " " << lb.get<1>() << ", "
                   << rb.get<0>() << " " << rb.get<1>() << ", "
                   << rt.get<0>() << " " << rt.get<1>() << ", "
                   << lt.get<0>() << " " << lt.get<1>() << ")";
        return out.str();
    }
    
protected:
    struct OnRight{
        bool operator()(const point &p1, const point &p2){
            return (p1.get<0>() < p2.get<0>());
        }
    };
};

typedef SimpleQuadrilateral squadrilateral;
typedef SimpleQuadrilateral quadrilateral;


}
}
#endif	/* GEOMETRY_HPP */

