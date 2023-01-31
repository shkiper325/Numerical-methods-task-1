#ifndef VEC_HPP
#define VEC_HPP

template <class T>
class Vec {
    T* data_;
    int size_;
public:
    Vec(int n);
    Vec(int n, T fill);
    Vec(int n, T* fill);

    Vec(const Vec&);
    Vec& operator=(const Vec&);

    int size() const;
    T& operator()(int i);
    const T& operator()(int i) const;

    template<class K>
    friend Vec<K> operator+(const Vec<K>&, const Vec<K>&);
    template<class K>
    friend Vec<K> operator-(const Vec<K>&, const Vec<K>&);
    template<class K>
    friend K operator*(const Vec<K>&, const Vec<K>&);
    template<class K>
    friend Vec<K> operator*(const K&, const Vec<K>&);

    T l2_norm() const;

    void print() const;
};

#include "Vec_impl.hpp"

using VecD = Vec<double>;

#endif