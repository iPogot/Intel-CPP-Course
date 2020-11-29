#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "vector.hpp"
#include <limits>

namespace triangle {

class Plane 
{
public:

    Plane();

    Plane(const Vector norm, const Point p);

    Plane(const Point p1, const Point p2, const Point p3);

    bool iscorrect();

    bool isparallel(Plane p) const;

    void print_equation() const;

    double sign_distance(const Point p) const;

    bool check_point(const Point p) const;

    bool operator==( Plane p ) const;

    Point find_common_point(const Plane p) const;

    double get_x() const;

    double get_y() const;

    double get_z() const;

    Vector get_norm() const;
    
    double get_d() const;

private:    

    Vector norm_;
    double d_; 

};





}

#endif
