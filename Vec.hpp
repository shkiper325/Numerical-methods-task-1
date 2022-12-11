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

    friend Vec operator+(const Vec&, const Vec&);
    friend Vec operator-(const Vec&, const Vec&);
    friend T operator*(const Vec&, const Vec&);
    friend Vec operator*(const T&, const Vec&);

    T l2_norm() const;
};

using VecD = Vec<double>;

#endif