#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "row.hpp"
#include <string>

namespace matrix { 

template <typename T> class Matrix {

public:
    Matrix(size_t size): sz_(size) {

        rows_ = (Row<T>*)malloc(sizeof(Row<T>) * size);
        
        if(rows_ == NULL) {
            throw "Memory allocation error";
        }
           
        for (int i = 0; i < size; i++) { 
            rows_[i].set(size);
        }

    }

    Matrix(const Matrix<T> &m): sz_(m.sz_) {

        rows_ = (Row<T>*)malloc(sizeof(Row<T>) * sz_);

        if(rows_ == NULL) {
            throw "Memory allocation error";
        }

        for(int i = 0; i < sz_; i++) {
            rows_[i] = m.rows_[i];
        }
        
    }

    ~Matrix() {
        free(rows_);
    }
    

public:
    T det() const {
        Row<T> tmp_r(sz_);
        Matrix<T> tmp_m = *this;
        bool sign = false;

        for(size_t j = 0; j < tmp_m.sz_; j++) {
            
            if(!tmp_m[j][j]) {
                
                tmp_r = tmp_m[j];
                
                for(size_t k = j + 1; k < tmp_m.sz_; k++) {
                    if(tmp_m[k][j]) {
                        tmp_m[j] = tmp_m[k];
                        tmp_m[k] = tmp_r;
                        sign = !sign;
                        break;
                    }
                }

            }

            for(size_t i = j + 1; i < tmp_m.sz_; i++) {

                if(tmp_m[j][j]) {
                    tmp_m[i] -= tmp_m[j] * tmp_m[i][j] / tmp_m[j][j];
                }

            }

        }

        if(sign) {
            tmp_m[0] *= -1;
        }

        bool have_null_col = true;
        
        T det = 1;

        for(size_t j = 0; j < tmp_m.sz_; j++) {
            det *= tmp_m[j][j];  
        }
        
        
        return det;
    }

    size_t get_size() const {
        return sz_;
    }

    void print() const {
        for(int i = 0; i < sz_; i++) {
            std::cout << "| ";
            for(int j = 0; j < sz_; j++) {
                std::cout << rows_[i][j];
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }
    }

    Row<T> operator [] (size_t row_num) const {
        if(row_num > sz_) {
			throw "Index is out of range";
		}

        return rows_[row_num]; 
	}

    Row<T>& operator [] (size_t row_num) {
        if(row_num > sz_) {
			throw "Index is out of range";
		}

        return rows_[row_num]; 
	}

private:
    Row<T>* rows_;
    size_t sz_;


};

template <typename T> Matrix<T> catch_from_stdout() {
    T data;
    size_t size = 0;
    std::cin >> size;
    
    matrix::Matrix <T> m(size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cin >> data;
            m[i][j] = data;
        }
        std::cout<<std::endl;
    }
    return m;
}


}