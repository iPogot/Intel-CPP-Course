#pragma once

#include <iostream>
#include <cstdlib>

namespace matrix { 

template <typename T> class Row {

public:
    Row(): sz_(0),
        data_(nullptr) {
    }
    
    Row(size_t size): sz_(size) {
        data_ = (T*) std::calloc(sz_, sizeof(T));
        if(data_ == NULL) {
            throw "Memory allocation error";
        }
    }

    Row(const Row<T> &row): sz_(row.sz_) {
        data_ = (T*) std::calloc(sz_, sizeof(T));

        if(data_ == NULL) {
            throw "Memory allocation error";
        }

        for(int i = 0; i < sz_; i++) {
            data_[i] = row.data_[i];
        }
    }

    ~Row() {
        free(data_);
    }


public:
    size_t get_size() const {
        return sz_;
    }

    void print() const {
        std::cout << std::endl;

        for(int i = 0; i < sz_; i++) {
            std::cout << "| ";
            std::cout << data_[i];
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }

public:
    T operator [] (size_t pos) const {
        if(pos > sz_) {
			throw "Index is out of range";
		}
		
        return data_[pos]; 
	}

    T& operator [] (size_t pos) {
        if(pos > sz_) {
			throw "Index is out of range";
		}
		
        return data_[pos]; 
	}

    Row operator + (const Row rhs) const {
        if(sz_ != rhs.get_size()) {
            throw "Trying to add two rows of different sizes";
        }

        Row tmp(sz_);

        for(size_t i = 0; i < sz_; i++) {
            tmp[i] = rhs[i] + data_[i];
        }

        return tmp;
    }

    Row operator - (const Row rhs) const {
        if(sz_ != rhs.get_size()) {
            throw "Trying to add two rows of different sizes";
        }

        Row tmp(sz_);

        for(size_t i = 0; i < sz_; i++) {
            tmp[i] = data_[i] - rhs[i];
        }

        return tmp;
    }

    Row operator * (const T rhs) const {
        Row tmp(sz_);
        for(size_t i = 0; i < sz_; i++) {
            tmp[i] = data_[i] * rhs;
        }
        return tmp;
    }

    Row operator / (const T rhs) const {
        Row tmp(sz_);

        for(size_t i = 0; i < sz_; i++) {
            tmp[i] = data_[i] / rhs;
        }

        return tmp;
    }

    Row& operator += (const Row& rhs) {
        if(sz_ != rhs.get_size()) {
            throw "Trying to add two rows of different sizes";
        }

        for(size_t i = 0; i < sz_; i++) {
            data_[i] += rhs[i];
        }

        return *this;
    }

    Row& operator -= (const Row rhs) {
        if(sz_ != rhs.get_size()) {
            throw "trying to subtract a row of a different length";
        }

        for(size_t i = 0; i < sz_; i++) {
            data_[i] -= rhs[i];
        }
        
        return *this;
    }

    Row& operator *= (const T rhs)  {

        for(size_t i = 0; i < sz_; i++) {
            data_[i] *= rhs;
        }

        return *this;

    }

    Row& operator /= (const T rhs)  {

        for(size_t i = 0; i < sz_; i++) {
            data_[i] /= rhs;
        }

        return *this;
    }


    void set (size_t size) {
        data_ = (T*) std::calloc(size, sizeof(T));
        sz_ = size;
    }

private:
    T* data_;
    size_t sz_ = 0;

};

}