#pragma once

#include <iostream>
#include <limits>


namespace triangle {

bool compare_doubles(const double x, const double y);

class Point 
{
public:

    Point() {};

    Point(const double x, const double y, const double z);
        
    
    Point(const Point& p);
    

    Point operator-(const Point p);

    bool operator==(const Point p);

    void print_coordinates() const;

    double get_x() const;
    double get_y() const;
    double get_z() const;

private:    
    double x_, y_, z_;

};



}
