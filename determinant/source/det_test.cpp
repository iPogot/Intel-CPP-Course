#include "matrix.hpp"
#include <gtest/gtest.h>


typedef double data_t;

TEST(Determinant, constructors) {
    
     matrix::Matrix <data_t> m1 (10);
     ASSERT_EQ(m1.get_size(), 10);

     for(size_t i = 0; i < 10; i++) {
          ASSERT_EQ(m1[i].get_size(), 10);
     }

}


TEST(Determinant, initialization) {
    
     matrix::Matrix <data_t> m (10);
     ASSERT_EQ(m.get_size(), 10);

     for(size_t i = 0; i < 10; i++) {
          ASSERT_EQ(m[i].get_size(), 10);
          //m[0][i] = i;
          for(size_t j = 0; j < 10; j++) {
               m[i][j] = j + 10 * i;
               
          }
          std::cout << "\n\n";
          m.print();

     }    

     m.print();

     for(size_t i = 0; i < 10; i++) {
          ASSERT_EQ(m[i].get_size(), 10);
          for(size_t j = 0; j < 10; j++) {
               m[i][j] = j + 10 * i;
               //std::cout << i << "  " << j << "  " << m[i][j] << std::endl;
               ASSERT_EQ(m[i][j], j + 10 * i);
          }
     }



}