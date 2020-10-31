#include "point.hpp"

namespace triangle {


Point::Point(const double x, const double y, const double z) {
    x_ = x; 
    y_ = y; 
    z_ = z;
}
        
    
Point::Point(const Point& p) {
    x_ = p.x_; 
    y_ = p.y_;
    z_ = p.z_; 
}
    

Point Point::operator-(const Point p) {
    Point tmp(*this);
    tmp.x_ -=  p.x_;
    tmp.y_ -=  p.y_;
    tmp.z_ -=  p.z_;
    
    return tmp;
};

bool Point::operator==(const Point p) {
    return compare_doubles(x_, p.x_) && compare_doubles(y_, p.y_) && compare_doubles(z_, p.z_);
};

void Point::print_coordinates() const {
    std::cout<< "x = " << x_ << " y = " << y_ << " z = " << z_ << std::endl;
};

double Point::get_x() const {
    return x_;
};

double Point::get_y() const {
    return y_;
};

double Point::get_z() const {
    return z_;
};


bool compare_doubles(const double x, const double y) {
    
    double epsilon = 1e-9;
    return (((y - x) < epsilon) && (-(y - x) < epsilon));
}

}