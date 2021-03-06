#include "vector.hpp"

namespace triangle {

Vector::Vector() {};
Vector::Vector(const Point  p1, Point p2): coordinates_(p2 - p1) {};
Vector::Vector(const Vector& v):  coordinates_(v.coordinates_) {};
Vector::Vector(const Point& p):  coordinates_(p) {};
Vector::Vector(const double x, const double y, const double z) {
    Point p(x, y, z);
    coordinates_ = p;
}


void Vector::print_coordinates() const {
    std::cout<< "x = " << coordinates_.get_x() << " y = " << coordinates_.get_y() << " z = " << coordinates_.get_z() << std::endl;
}

Vector Vector::operator*(Vector v) {
    double a1, a2, b1, b2, c1, c2;
    double a, b, c;
    
    a1 = coordinates_.get_x();
    b1 = coordinates_.get_y();
    c1 = coordinates_.get_z();

    a2 = v.coordinates_.get_x();
    b2 = v.coordinates_.get_y();
    c2 = v.coordinates_.get_z();

    a = b1 * c2 - b2 * c1;
    b = a2 * c1 - a1 * c2;
    c = a1 * b2 - b1 * a2;
    
    Point p(a, b, c);
    Vector res(p);

    return res;
}

double Vector::dot_product(const Vector v) {

    return get_x() * v.get_x() + get_y() * v.get_y() + get_z() * v.get_z();

}

bool Vector::operator==(const Vector v) {

    return coordinates_==v.coordinates_;

}

double Vector::get_x() const {

    return coordinates_.get_x();

}

double Vector::get_y() const {

    return coordinates_.get_y();

}

double Vector::get_z() const {

    return coordinates_.get_z();

}

}