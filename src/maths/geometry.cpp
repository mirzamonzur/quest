/* 
 * File:   geometry.hpp
 * Author: K M Masum Habib<masum.habib@virginia.edu>
 *
 * Created on February 3, 2014, 1:45 PM
 */

#include "geometry.hpp"
#include "../python/boostpython.hpp"


namespace qmicad{
namespace python{

/**
 * Geometry python wrappers.
 */

void export_point(){
    using namespace maths::geometry;

    class_<point, shared_ptr<point> >("Point", 
            init<const double&, const double&>())
        .def_pickle(PointPickler())
    ;
}


void export_quadrilateral(){
    using namespace maths::geometry;

    class_<quadrilateral, bases<Printable>, shared_ptr<quadrilateral> >("Quadrilateral", 
            init<const point&, const point&, const point&, 
            const point&, optional<const string&> >())
        .def_pickle(QuadrilateralPickler())
    ;
}

}
}