#pragma once

#include "line.hpp"
#include "plane.hpp"
#include "vector.hpp"
#include "point.hpp"
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>


#include <iostream>

namespace triangle {

class Triangle 
{

public:
    Triangle(const Point p1, const Point p2, const Point p3);

    void print_triangle_info() const;

    double sign_distance(const Point p) const;

    std::vector<Point> get_points_() const;

    Plane get_plane() const;
    
    bool check_intesection(Triangle tr) const;

private:    
    std::vector<Point> points_;
    Plane plane_;

    bool is_point;
    bool is_line;
    bool is_triangle;


};

bool is_point_inside(float x1, float y1, float x2, float y2, float x3, float y3, float x, float y);
double calc_area(double x1, double y1, double x2, double y2, double x3, double y3);

}

