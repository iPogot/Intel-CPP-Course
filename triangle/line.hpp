#pragma once

#include "point.hpp"
#include "plane.hpp"
#include "vector.hpp"

namespace triangle {

class Line {

public:
    
    Line();

    Line(const Point p1, const Point p2);

    Line(const Plane p1, const Plane p2);

    void print_line() const;

    Vector get_vector() const;

    Point get_point() const;

    double get_parameter(const Point p);

    bool find_intersection(const Line l, Point& p);


private:
    Vector v_;
    Point p0_;

};

}
