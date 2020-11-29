#include "line.hpp"

namespace triangle {

Line::Line() {};

Line::Line(const Point p1, const Point p2): v_(p2, p1), p0_(p1) {};

Line::Line(const Plane p1, const Plane p2): v_(p1.get_norm() * p2.get_norm()) {

    p0_ = p1.find_common_point(p2);

}

void Line::print_line() const {
    std::cout<<"x = "<<v_.get_x()<<" * t + "<<p0_.get_x()<<std::endl;
    std::cout<<"y = "<<v_.get_y()<<" * t + "<<p0_.get_y()<<std::endl;
    std::cout<<"z = "<<v_.get_z()<<" * t + "<<p0_.get_z()<<std::endl;
}

Vector Line::get_vector() const {
    return v_;
}

Point Line::get_point() const {
    return p0_; 
}

double Line::get_parameter(const Point p) {
    
    if(v_.get_x()) {

        return (p.get_x() - p0_.get_x()) / v_.get_x();

    } else if(v_.get_y()) {

        return (p.get_y() - p0_.get_y()) / v_.get_y();

    } else if(v_.get_z()) {

        return (p.get_z() - p0_.get_z()) / v_.get_z();

    }

}

bool Line::find_intersection(const Line l, Point& p) {

    //a0*x+b0*y=d0
    //a1*x+b1*y=d1

    double a0, b0, d0, a1, b1, d1;

    if( compare_doubles(v_.get_z(), 0) && compare_doubles(l.get_vector().get_z(), 0) ) { //xy

        a0 = v_.get_y();
        a1 = l.get_vector().get_y();

        b0 = -v_.get_x();
        b1 = -l.get_vector().get_x();


        d0 = -v_.get_x() * p0_.get_y() + v_.get_y() * p0_.get_x();
        d1 = - l.get_vector().get_x() * l.get_point().get_y() + l.get_vector().get_y() * l.get_point().get_x();

        std::cout << "\n\n" << a0 << " * x + " << b0 << " * y = " << d0 << std::endl;
        std::cout << "\n\n" << a1 << " * x + " << b1 << " * y = " << d1 << std::endl;
        
        double det = a0 * b1 - a1 * b0;
        if(!compare_doubles(det, 0)) {

            p = Point( (d0*b1 - b0*d1) / det, (a0*d1 - a1*d0) / det, 0);
            return true;

        } else {

            return false;

        }

    } else if( compare_doubles(v_.get_y(), 0) && compare_doubles(l.get_vector().get_y(), 0) ) { //xz

        a0 = v_.get_z();
        a1 = l.get_vector().get_z();

        b0 = -v_.get_x();
        b1 = -l.get_vector().get_x();

        d0 = -v_.get_x() * p0_.get_z() + v_.get_z() * p0_.get_x();
        d1 = -l.get_vector().get_x() * l.get_point().get_z() + l.get_vector().get_z() * l.get_point().get_x();

        double det = a0 * b1 - a1 * b0;
        if(!compare_doubles(det, 0)) {

            p = Point( (d0*b1 - b0*d1) / det,0 , (a0*d1 - a1*d0) / det );
            return true;

        } else {

            return false;

        }            

    } else if(compare_doubles(v_.get_x(), 0) && compare_doubles(l.get_vector().get_x(), 0)) { //yz


        a0 = v_.get_z();
        a1 = l.get_vector().get_z();

        b0 = -v_.get_y();
        b1 = -l.get_vector().get_y();

        d0 = -v_.get_y() * p0_.get_z() + v_.get_z() * p0_.get_y();
        d1 = -l.get_vector().get_y() * l.get_point().get_z() + l.get_vector().get_z() * l.get_point().get_y();

        double det = a0 * b1 - a1 * b0;

        if(!compare_doubles(det, 0)) {

            p = Point(0 ,(d0*b1 - b0*d1) / det, (a0*d1 - a1*d0) / det);
            return true;

        } else {

            return false;

        }            

    } else {

        return false;

    }

}

}