#include <gtest/gtest.h>
#include "matrix.hpp"
#include <stdio.h>

typedef double data_t;

int main() {

    try {
        
        matrix::Matrix <data_t> m = matrix::catch_from_stdout<data_t>();

        data_t det = m.det();
        
        printf("%lf", det);
    
    } catch(const char* e) {

        std::cerr << "Error: " << e << "\n";

    }
    
    return 0;

}