#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "vector.hpp"
#include <limits>

namespace triangle {

class Plane 
{
public:

    Plane() {};

    Plane(const Vector norm, const Point p) {

        double d = norm.get_x() * p.get_x() + norm.get_y() * p.get_y() + norm.get_z() * p.get_z();
        
        if(!d) {
            norm_ = Vector(norm.get_x(), norm.get_y(), norm.get_z());
            d_ = 0;
        } else {
            norm_ = Vector(norm.get_x() / d, norm.get_y() / d, norm.get_z() / d);
            d_ = 1;
        }

    }

    Plane(const Point p1, const Point p2, const Point p3) {

        auto norm = Vector(p1, p2) * Vector(p1, p3);
        double d = norm.get_x() * p1.get_x() + norm.get_y() * p1.get_y() + norm.get_z() * p1.get_z();
        
        if(!d) {
            norm_ = Vector(norm.get_x(), norm.get_y(), norm.get_z());
            d_ = 0;
        } else {
            norm_ = Vector(norm.get_x() / d, norm.get_y() / d, norm.get_z() / d);
            d_ = 1;
        }

    }

    bool iscorrect() {

        if( !get_x() && !get_y() && !get_z() ) {
            return false;
        } else {
            return true;
        }

    }

    bool isparallel(Plane p) const {

        double x = get_x();
        double y = get_y();
        double z = get_z();

        double p_x = p.get_x();
        double p_y = p.get_y();
        double p_z = p.get_z();

        bool is_x_null = compare_doubles(x, 0);
        bool is_y_null = compare_doubles(y, 0);
        bool is_z_null = compare_doubles(z, 0);
        
        bool is_xp_null = compare_doubles(p_x, 0);
        bool is_yp_null = compare_doubles(p_y, 0);
        bool is_zp_null = compare_doubles(p_z, 0);

        if( !is_xp_null && !is_yp_null && !is_zp_null ) {

            return compare_doubles(x / p_x,  y / p_y) && compare_doubles(y / p_y, z / p_z);

        } else if( is_xp_null && !is_yp_null && !is_zp_null) {

            if( is_y_null || is_z_null || !is_x_null ) {
                return false;
            } else {
                return compare_doubles(y / p_y, z / p_z);
            }

        } else if( !is_xp_null && is_yp_null && !is_zp_null) {

            if( is_x_null || is_z_null || !is_y_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, z / p_z);
            }
            
        } else if( !is_xp_null && !is_yp_null && is_zp_null ) {

            if( is_x_null || is_y_null || !is_zp_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, y / p_y);
            }

        } else if( is_xp_null && is_yp_null && !is_zp_null) {

            if( is_z_null || !is_x_null || !is_y_null ) {
                return false;
            } else {
                return true;
            }

        } else if( !is_xp_null && is_yp_null && is_zp_null ) {
            
            if( is_x_null || !is_y_null || !is_z_null ) {
                return false;
            } else {
                return true;
            }

        } else if( is_xp_null && !is_yp_null && is_zp_null ) {

            if( is_y_null || !is_x_null || !is_z_null ) {
                return false;
            } else {
                return true;
            }

        } else {
            
            return false;

        }

    }

    void print_equation() const {

        std::cout << norm_.get_x() << " * x + " << norm_.get_y() << " * y + " << norm_.get_z() << " *  z" << " = "<<d_<< std::endl;

    };

    double sign_distance(const Point p) const {   

        return norm_.get_x() * p.get_x() + norm_.get_y() * p.get_y() + norm_.get_z() * p.get_z() - d_;

    };

    bool check_point(const Point p) const {

        return compare_doubles(p.get_x() * norm_.get_x() + p.get_y() * norm_.get_y() + p.get_z() * norm_.get_z(), d_);

    }

    bool operator==( Plane p ) const {

        double x = get_x();
        double y = get_y();
        double z = get_z();
        double d = d_;

        double p_x = p.get_x();
        double p_y = p.get_y();
        double p_z = p.get_z();
        double p_d = p.get_d();

        bool is_x_null = compare_doubles(x, 0);
        bool is_y_null = compare_doubles(y, 0);
        bool is_z_null = compare_doubles(z, 0);
        bool is_d_null = compare_doubles(d, 0);
        
        bool is_xp_null = compare_doubles(p_x, 0);
        bool is_yp_null = compare_doubles(p_y, 0);
        bool is_zp_null = compare_doubles(p_z, 0);
        bool is_dp_null = compare_doubles(p_d, 0);

        if( !is_xp_null && !is_yp_null && !is_zp_null && !is_dp_null ) {
        
            return compare_doubles(x / p_x,  y / p_y) && compare_doubles(y / p_y, z / p_z) && compare_doubles(z / p_z,  d / p_d);

        } else if( !is_xp_null && !is_yp_null && !is_zp_null && is_dp_null ) {
            
            return compare_doubles(x / p_x,  y / p_y) && compare_doubles(y / p_y,  z / p_z);

        } else if( !is_xp_null && !is_yp_null && is_zp_null && !is_dp_null ) {

            if( is_x_null && is_y_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, y / p_y) && compare_doubles(y / p_y, d / p_d);
            }

        } else if( !is_xp_null && is_yp_null && !is_zp_null && !is_dp_null ) {

            if( is_x_null && is_z_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, z / p_z) && compare_doubles(z / p_z, d / p_d);
            }   

        } else if( is_xp_null && !is_yp_null && !is_zp_null && !is_dp_null ) {

            if( is_y_null && is_z_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(y / p_y, z / p_z) && compare_doubles(z / p_z, d / p_d);
            }   

        } else if( !is_xp_null && !is_yp_null && is_zp_null && is_dp_null ) {

            if( is_x_null && is_y_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, y / p_y);
            }  

        } else if( !is_xp_null && is_yp_null && !is_zp_null && is_dp_null ) {

            if( is_x_null && is_z_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, z / p_z);
            }

        } else if( !is_xp_null && is_yp_null && is_zp_null && !is_dp_null ) {

            if( is_x_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(x / p_x, d / p_d);
            }

        } else if( is_xp_null && !is_yp_null && !is_zp_null && is_dp_null ) {

            if( is_y_null && is_z_null ) {
                return false;
            } else {
                return compare_doubles(y / p_y, z / p_z);
            }

        } else if( is_xp_null && !is_yp_null && is_zp_null && !is_dp_null ) {

            if( is_y_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(y / p_y, d / p_d);
            }

        } else if( is_xp_null && is_yp_null && !is_zp_null && !is_dp_null ) {

            if( is_z_null && is_d_null ) {
                return false;
            } else {
                return compare_doubles(z / p_z, d / p_d);
            }

        } else if( !is_xp_null ) {

            if( !is_x_null && is_y_null && is_z_null && is_d_null) {
                return true;
            } else {
                return false;
            }

        } else if( !is_yp_null ) {

            if( is_x_null && !is_y_null && is_z_null && is_d_null) {
                return true;
            } else {
                return false;
            }

        } else if( !is_zp_null ) {

            if( is_x_null && is_y_null && !is_z_null && is_d_null) {
                return true;
            } else {
                return false;
            }

        } else {

            return false;
        
        }

    }

    Point find_common_point(const Plane p) const {

        double res_x;
        double res_y;
        double res_z;
        double res_d;
        
        double x = get_x();
        double y = get_y();
        double z = get_z();
        double d = d_;

        double p_x = p.get_x();
        double p_y = p.get_y();
        double p_z = p.get_z();
        double p_d = p.get_d();

        bool is_x_null = compare_doubles(x, 0);
        bool is_y_null = compare_doubles(y, 0);
        bool is_z_null = compare_doubles(z, 0);
        bool is_d_null = compare_doubles(d, 0);
        
        bool is_xp_null = compare_doubles(p_x, 0);
        bool is_yp_null = compare_doubles(p_y, 0);
        bool is_zp_null = compare_doubles(p_z, 0);
        bool is_dp_null = compare_doubles(p_d, 0);


        if( is_d_null && is_dp_null ) {
            
            res_x = 0;
            res_y = 0;
            res_z = 0;

        } else if( !is_x_null && !is_y_null && !is_xp_null && !is_yp_null ) {
            
            res_z = 0;
            res_y = (p_d * x - d * p_x) / (p_y * x - y * p_x);
            res_x = (d - res_y * y) / x;

        } else if( !is_y_null && !is_z_null && !is_yp_null && !is_zp_null ) {

            res_x = 0;
            res_y = (p_d * z - d * p_z) / (p_y * z - y * p_z);
            res_z = (d - res_y * y) / z;

        } else if( !is_x_null && !is_z_null && !is_xp_null && !is_zp_null ) {

            res_y = 0;
            res_x = (p_d * z - d * p_z) / (p_x * z - x * p_z);
            res_z = (d - res_x * x) / z;
            
        } else if( !is_x_null && is_y_null && is_z_null ) {
            
            res_x = d / x;
            if( !is_yp_null ){

                res_z = 0;
                res_y = (p_d - res_x * p_x) / p_y;

            } else if( !is_zp_null ) {
                
                res_y = 0;
                res_z = (p_d - res_x * p_x) / p_z;  

            }

        } else if ( is_x_null && !is_y_null && is_z_null ) {
        
            res_y = d / y;
            if( !is_xp_null ){

                res_z = 0;
                res_x = (p_d - res_y * p_y) / p_x;

            } else if( !is_zp_null ) {
                
                res_x = 0;
                res_z = (p_d - res_y * p_y) / p_z;  

            }

        } else if ( is_x_null && is_y_null && !is_z_null ) {
        
            res_z = d / z;
            if( !is_xp_null ){

                res_y = 0;
                res_x = (p_d - res_z * p_z) / p_x;

            } else if( !is_yp_null ) {
                
                res_x = 0;
                res_y = (p_d - res_z * p_z) / p_y;  

            }

        } else if ( !is_xp_null && is_yp_null && is_zp_null ) {
        
            res_x = p_d / p_x;
            if( !is_y_null ){

                res_z = 0;
                res_y = (d - res_x * x) / y;

            } else if( !is_z_null ) {
                
                res_y = 0;
                res_z = (d - res_x * x) / z;  

            }
        
        } else if ( is_xp_null && !is_yp_null && is_zp_null ) {
        
            res_y = p_d / p_y;
            if( !is_x_null ){

                res_z = 0;
                res_x = (d - res_y * y) / x;

            } else if( !is_z_null ) {
                
                res_x = 0;
                res_z = (d - res_y * y) / z;  

            }
        
        } else if ( is_xp_null && is_yp_null && !is_zp_null ) {
        
            res_z = p_d / p_z;
            if( !is_x_null ){

                res_y = 0;
                res_x = (d - res_z * z) / x;

            } else if( !is_y_null ) {
                
                res_x = 0;
                res_y = (d - res_z * z) / y;  

            }

        }
        
        return Point(res_x, res_y, res_z);

    }

    double get_x() const {

        return norm_.get_x();

    };

    double get_y() const {

        return norm_.get_y();

    };

    double get_z() const {

        return norm_.get_z();

    };

    Vector get_norm() const {

        return norm_;

    }
    
    double get_d() const {

        return d_;

    };

private:    

    Vector norm_;
    double d_; 

};





}

#endif
