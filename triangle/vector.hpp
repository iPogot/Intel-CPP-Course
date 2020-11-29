#pragma once

#include <iostream>
#include "point.hpp"

namespace triangle {

class Vector 
{
public:

    Vector();
    Vector(const Point  p1, Point p2);
    Vector(const Vector& v);
    Vector(const Point& p);
    Vector(const double x, const double y, const double z);


    void print_coordinates() const;

    double dot_product(const Vector v);

    bool operator==(const Vector v);
    Vector operator*(Vector v);

    double get_x() const;
    double get_y() const;
    double get_z() const;
        
private:

    Point coordinates_; 
    
};    

}