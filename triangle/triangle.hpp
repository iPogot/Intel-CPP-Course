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
    Triangle(const Point p1, const Point p2, const Point p3): plane_(p1, p2, p3) {

        points_.emplace_back(p1);
        points_.emplace_back(p2);
        points_.emplace_back(p3);

    }

    void print_triangle_info() const {

        //std::cout<<"Plane:"<<std::endl;
        plane_.print_equation();
        //std::cout<<"point1"<<std::endl;
        points_[0].print_coordinates();
        //std::cout<<"point2"<<std::endl;
        points_[1].print_coordinates();
        //std::cout<<"point3"<<std::endl;
        points_[2].print_coordinates();

    }

    double sign_distance(const Point p) const {  

        return plane_.sign_distance(p);

    }

    std::vector<Point> get_points_() const {

        return points_;

    }
    
    Plane get_plane() const {

        return plane_;

    }

    bool check_intesection(Triangle tr) const {
        
        Plane plane_0 = plane_;
        Plane plane_1 = tr.get_plane();

        std::vector<Point> points_0 = points_;
        std::vector<Point> points_1 = tr.get_points_();

        std::vector<double> sign_dist_0;
        std::vector<double> sign_dist_1;

        for (Point p : points_1) {

            sign_dist_1.emplace_back(plane_0.sign_distance(p));

        }

        for (Point p : points_0) {

            sign_dist_0.emplace_back(plane_1.sign_distance(p));

        }

        if ( (sign_dist_1[0] > 0 && sign_dist_1[1] > 0 && sign_dist_1[2] > 0) || (sign_dist_1[0] < 0 && sign_dist_1[1] < 0 && sign_dist_1[2] < 0) ) {
            
            return false;

        }

        if ( plane_0.isparallel(plane_1) ) {

            if( plane_0 == plane_1 ) {
                std::vector<Point> p0;
                std::vector<Point> p1;

                std::vector<Line> l0;
                std::vector<Line> l1;

                bool xy = false;
                bool yz = false;
                bool xz = false;

                if ( fabs(plane_0.get_norm().get_x()) <= fabs(plane_0.get_norm().get_z()) && 
                        fabs(plane_0.get_norm().get_y()) <= fabs(plane_0.get_norm().get_z()) ) {   
                        
                    for (size_t i = 0; i < 3; i++) {
                        p0.emplace_back(Point(points_0[i].get_x(), points_0[i].get_y(), 0));
                    } 


                    for (size_t i = 0; i < 3; i++) {
                        p1.emplace_back(Point(points_1[i].get_x(), points_1[i].get_y(), 0));
                    }

                    xy = true;

                } else if ( fabs(plane_0.get_norm().get_y()) <= fabs(plane_0.get_norm().get_x()) && 
                    fabs(plane_0.get_norm().get_z()) <= fabs(plane_0.get_norm().get_x()) ) {

                    for (size_t i = 0; i < 3; i++) {
                        p0.emplace_back(Point(0, points_0[i].get_y(), points_0[i].get_z()));
                    } 
                    
                    for (size_t i = 0; i < 3; i++) {
                        p1.emplace_back(Point(0, points_1[i].get_y(), points_1[i].get_z()));
                    }

                    yz = true;

                } else if ( fabs(plane_0.get_norm().get_x()) <= fabs(plane_0.get_norm().get_y()) && 
                    fabs(plane_0.get_norm().get_z()) <= fabs(plane_0.get_norm().get_y()) ) {
                        
                    for (size_t i = 0; i < 3; i++) {
                        p0.emplace_back(Point(points_0[i].get_x(), 0, points_0[i].get_z()));
                    } 

                    
                    for (size_t i = 0; i < 3; i++) {
                        p1.emplace_back(Point(points_1[i].get_x(), 0, points_1[i].get_z()));
                    }

                    xz = true;

                }
                
                Point inters_p;

                l0.emplace_back(p0[0], p0[1]);
                l0.emplace_back(p0[1], p0[2]);
                l0.emplace_back(p0[2], p0[0]);

                l1.emplace_back(p1[0], p1[1]);
                l1.emplace_back(p1[1], p1[2]);
                l1.emplace_back(p1[2], p1[0]);
                
                for(size_t i = 0; i < 3; ++i) {
                    for(size_t j = 0; j < 3; ++j) {

                        if (l0[i].find_intersection(l1[j], inters_p)) {

                            double x = inters_p.get_x();
                            double y = inters_p.get_y();
                            double z = inters_p.get_z();
                            
                            if(xy || xz) {
                                
                                Vector v0 = l0[i].get_vector();
                                Vector v1 = l1[i].get_vector();

                                if( (p0[i].get_x() <= x && x <= p0[(i+1)%3].get_x() || p0[(i+1)%3].get_x() <= x && x <= p0[i].get_x()) &&
                                    (p1[i].get_x() <= x && x <= p1[(i+1)%3].get_x() || p1[(i+1)%3].get_x() <= x && x <= p1[i].get_x()) ) {

                                        return true;

                                } 

                            } else if(yz) {

                                if( (p0[i].get_y() <= y && y <= p0[(i+1)%3].get_y() || p0[(i+1)%3].get_y() <= y && y <= p0[i].get_y()) &&
                                    (p1[i].get_y() <= y && y <= p1[(i+1)%3].get_y() || p1[(i+1)%3].get_y() <= y && y <= p1[i].get_y()) ) {

                                        return true;

                                } 

                            }
                            
                        }

                    }

                }
               
                return false;

            } else {


                return false; 

            }        
            
            return false;
        }

        if ( (sign_dist_0[0] > 0 && sign_dist_0[1] > 0 && sign_dist_0[2] > 0) || (sign_dist_0[0] < 0 && sign_dist_0[1] < 0 && sign_dist_0[2] < 0) ) {

            return false;

        }

        Line inter_line(plane_0, plane_1);

        bool is_pos_oriented_0 = false;
        bool is_neg_oriented_0 = false;
        bool is_one_vert_on_line_0 = false;
        bool is_two_vert_on_line_0 = false;
        bool is_pos_oriented_1 = false;
        bool is_neg_oriented_1 = false;
        bool is_one_vert_on_line_1 = false;
        bool is_two_vert_on_line_1 = false;

        size_t cnt_pos_vert_0 = 0;
        size_t cnt_neg_vert_0 = 0;
        size_t cnt_null_vert_0 = 0;
        size_t cnt_pos_vert_1 = 0;
        size_t cnt_neg_vert_1 = 0;
        size_t cnt_null_dist_1 = 0;

        std::vector<size_t> pos_vert_0;
        std::vector<size_t> neg_vert_0;
        std::vector<size_t> null_vert_0;

        std::vector<size_t> pos_vert_1;
        std::vector<size_t> neg_vert_1;
        std::vector<size_t> null_vert_1;

        std::vector<double> v0;
        std::vector<double> v1;

        for (size_t i = 0; i < 3; i++) {

            if (sign_dist_0[i] > 0) {

                pos_vert_0.emplace_back(i);

            } else if (sign_dist_0[i] < 0) {

                neg_vert_0.emplace_back(i);
              
            } else if (sign_dist_0[i] == 0) {
                
                null_vert_0.emplace_back(i);
            
            }

            v0.emplace_back(inter_line.get_vector().dot_product(Vector(inter_line.get_point(), points_0[i])));
            
        }


        for (int i = 0; i < 3; i++) {

            if (sign_dist_1[i] > 0) {
            
                pos_vert_1.emplace_back(i);
            
            } else if (sign_dist_1[i] < 0) {
            
                neg_vert_1.emplace_back(i);
            
            } else if (sign_dist_1[i] == 0) {
            
                null_vert_1.emplace_back(i);
            
            }

            v1.emplace_back(inter_line.get_vector().dot_product(Vector(inter_line.get_point(), points_1[i])));
            
        }
            
        std::vector<double> t0;
        std::vector<double> t1;

        if(pos_vert_0.size() == 2) {
            if(neg_vert_0.size() == 1) {

                for (size_t i : pos_vert_0) {

                    t0.emplace_back(v0[i] + (v0[neg_vert_0[0]] - v0[i]) * sign_dist_0[i] / (sign_dist_0[i] - sign_dist_0[neg_vert_0[0]]));

                }

            }
             
        } else if(neg_vert_0.size() == 2) {
            if(pos_vert_0.size() == 1) {

                for (size_t i : neg_vert_0) {

                    t0.emplace_back(v0[i] + (v0[pos_vert_0[0]] - v0[i]) * sign_dist_0[i] / (sign_dist_0[i] - sign_dist_0[pos_vert_0[0]]));
                
                }

            }

        } else if(null_vert_0.size() == 2) {

            t0.emplace_back(inter_line.get_parameter(points_0[null_vert_0[0]]));
            t0.emplace_back(inter_line.get_parameter(points_0[null_vert_0[1]]));

        } else if(null_vert_0.size() == 1) {

            t0.emplace_back(inter_line.get_parameter(points_0[null_vert_0[0]]));

        }
        
        
        if(pos_vert_1.size() == 2) {

            if(neg_vert_1.size() == 1) {
                
                for (size_t i : pos_vert_1) {

                    t1.emplace_back(v1[i] + (v1[neg_vert_1[0]] - v1[i]) * sign_dist_1[i] / (sign_dist_1[i] - sign_dist_1[neg_vert_1[0]]));
                   
                }

            }
            
             
        } else if(neg_vert_1.size() == 2) {

            if(pos_vert_1.size() == 1) {

                for (size_t i : neg_vert_1) {

                    t1.emplace_back(v1[i] + (v1[pos_vert_1[0]] - v1[i]) * sign_dist_1[i] / (sign_dist_1[i] - sign_dist_1[pos_vert_1[0]]));
            
                }

            } 

        } else if(null_vert_1.size() == 2) {

            t1.emplace_back(inter_line.get_parameter(points_1[null_vert_1[0]]));
            t1.emplace_back(inter_line.get_parameter(points_1[null_vert_1[1]]));

        } else if(null_vert_1.size() == 1) {

            t1.emplace_back(inter_line.get_parameter(points_1[null_vert_1[0]]));

        }

        if(t0.size() == 2 && t1.size() == 2) {

            if(t1[0] <= t0[1] && t0[1] <= t1[1] || t1[0] <= t0[0] && t0[0] <= t1[1] || t0[0] <= t1[0] && t1[0] <= t0[1]) {
                return true;

            } else return false;

        } else if(t0.size() == 2 && t1.size() == 1) {
            
            if(t0[0] <= t1[0] <= t0[1]) {

                return true;

            } else return false;

        } else if(t0.size() == 1 && t1.size() == 2) {

            if(t1[0] <= t0[0] <= t1[1]) {

                return true;

            } else return false;

        } else if(t0.size() == 1 && t1.size() == 1) {

            if(compare_doubles(t0[0], t1[0])) {

                return true;

            } else return false;

        }
        

    }

private:    
    std::vector<Point> points_;
    Plane plane_;


};

}

