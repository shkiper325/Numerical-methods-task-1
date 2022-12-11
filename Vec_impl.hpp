#ifndef VEC_IMPL_HPP
#define VEC_IMPL_HPP

#include <cmath>

#include "Vec.hpp"

template <class T>
Vec<T>::Vec(int n) : size_(n) {
    if (n <= 0) throw -1;

    data_ = new T[n];
}

template <class T>
Vec<T>::Vec(int n, T fill) : size_(n) {
    if (n <= 0) throw -1;

    data_ = new T[n];

    for(int i = 0; i < n; ++i) {
        data_[i] = fill;
    }
}

template <class T>
Vec<T>::Vec(int n, T* fill) : size_(n) {
    if (n <= 0) throw -1;

    data_ = new T[n];

    memcpy(data_, fill, n * sizeof(T));
}

template <class T>
Vec<T>::Vec(const Vec& other) : size_(other.size_){
    data_ = new T[n];

    memcpy(data_, other.data_, size_ * sizeof(T));
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    size_ = other.size_;

    delete [] data_;
    data_ = new T[n];

    memcpy(data_, other.data_, size_ * sizeof(T));
}

template <class T>
int Vec<T>::size() const {
    return size_;
}

template <class T>
T& Vec<T>::operator()(int i) {
    return data_[i];
}

template <class T>
Vec<T> operator+(const Vec<T>& a, const Vec<T>& b) {
    if (a.size_ != b.size_) {
        throw -1;
    }

    Vec<T> ret(a.size_);

    for(int i = 0; i < a.size_; ++i) {
        ret.data_[i] = a.data_[i] + b.data_[i];
    }
    
    return ret;
}

template <class T>
Vec<T> operator-(const Vec<T>& a, const Vec<T>& b) {
    if (a.size_ != b.size_) {
        throw -1;
    }

    Vec<T> ret(a.size_);

    for(int i = 0; i < a.size_; ++i) {
        ret.data_[i] = a.data_[i] - b.data_[i];
    }
    
    return ret;
}

template <class T>
T operator*(const Vec<T>& a, const Vec<T>& b) {
    if (a.size_ != b.size_) {
        throw -1;
    }

    T ret = 0;

    for(int i = 0; i < a.size_; ++i) {
        ret += a.data_[i] * b.data_[i];
    }
    
    return ret;
}

template <class T>
Vec<T> operator*(T& a, const Vec<T>& b) {
    Vec<T> ret(b.size_);

    for(int i = 0; i < a.size_; ++i) {
        ret.data_[i] = a * b.data_[i];
    }
    
    return ret;
}

template <class T>
T Vec<T>::l2_norm() const {
    T ret = 0;

    for(int i = 0; i < size_; ++i) {
        ret += data_[i] * data[i];
    }

    return std::sqrt(ret);
}

#endif