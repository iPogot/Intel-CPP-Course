#include "triangle.hpp"
#include <stdio.h>
#include <vector>
#include <map>


int main() {
    
    size_t tr_cnt = 0;
    size_t total_cnt_num = 0;

    double num = 0;
    size_t num_cnt = 0;
    
    std::vector<double> num_array;
    std::vector<triangle::Point> point_array;
    std::vector<triangle::Triangle> triangle_array;
    auto ret = scanf("%zu", &total_cnt_num);                  //skip first number
    //total_cnt_num = 2;
    double x, y, z;
    triangle::Point p1, p2, p3;

    while(tr_cnt < total_cnt_num) {

        ret = scanf("%lf", &num);

        num_array.emplace_back(num);
        num_cnt++;

        if(num_cnt % 3 == 0) {

            x = num_array[0];
            y = num_array[1];
            z = num_array[2];

            num_array.pop_back();
            num_array.pop_back();
            num_array.pop_back();
            point_array.emplace_back(triangle::Point(x, y, z));

            if(num_cnt == 9) {
                
                tr_cnt++;

                p1 = point_array[0];
                p2 = point_array[1];
                p3 = point_array[2];
                point_array.pop_back();
                point_array.pop_back();
                point_array.pop_back();
                triangle_array.emplace_back(triangle::Triangle(p1, p2, p3));
                
                num_cnt = 0; 
            
            }

        } 

    }
    
    
    std::map<size_t, bool> inter_tr;
    for(auto i = 0; i < triangle_array.size(); i++) {
        for(auto j = i + 1; j < triangle_array.size(); j++) {
            
            if( triangle_array[i].get_plane().iscorrect() && triangle_array[j].get_plane().iscorrect() ) {
                
                if(triangle_array[i].check_intesection(triangle_array[j])) {

                    if(inter_tr.find(i) == inter_tr.end()) {
                        inter_tr.insert({i, true});
                    }
                    if(inter_tr.find(j) == inter_tr.end()) {
                        inter_tr.insert({j, true});
                    }
                }

            }
            
        }
    }

    for(auto it = inter_tr.begin(); it != inter_tr.end(); it++) {

        std::cout<<it->first + 1<<std::endl;

    }


    return 0;
}