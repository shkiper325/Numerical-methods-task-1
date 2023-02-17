#ifndef POLY_HPP
#define POLY_HPP

#include <vector>
#include <algorithm>
#include <iostream>

#include <cstdlib>

#include "error.hpp"

extern const double k1;
extern const double k2;

class Poly {
    std::vector<double> coeff_;
    bool is_zero_;
    double eps_;
public:
    Poly(std::vector<double> coeff, double eps=1e-14) {
        while(true) {
            if(coeff.size() == 0) {
                break;
            }

            if(abs(coeff.back()) < eps) {
                coeff.pop_back();
            } else {
                break;
            }
        } 

        coeff_ = coeff;
        is_zero_ = coeff.size() == 0;
        eps_ = eps;
    }

    int deg() const {
        return static_cast<int>(coeff_.size()) - 1;
    }

    double operator()(double x) const {
        int d = deg(); 
        
        if(d == -1) return 0;
        else {
            double ret = 0;

            for(int i = d; i >= 0; --i) {
                ret *= x;
                ret += coeff_[i];
            }

            return ret;
        }
    }

    Poly derivative() const {
        int d = deg();

        if (d == -1 || d == 0) {
            return Poly({0});
        } else {
            std::vector<double> result(d);

            for (int i = 0; i < d; ++i) {
                result[i] = (i + 1) * coeff_[i + 1];
            }

            return Poly(result);
        }
    }

    double integrate(double a, double b) const {
        int d = deg();

        std::vector<double> result(d + 2);

        result[0] = 0;
        for(int i = 1; i < d + 2; ++i) {
            result[i] = coeff_[i - 1] / i;
        }

        Poly ad(result);

        return ad(b) - ad(a);
    }

    void print() const {
        int d = deg();

        if(d == -1) std::cout << 0;
        else {
            for(int i = 0; i < d + 1; ++i) {
                if(i == 0) std::cout << coeff_[0];
                else if(i == 1) {
                    if(abs(coeff_[i]) < eps_) {
                        continue;
                    }
                    else if(coeff_[i] > 0) {
                        std::cout << "+" << coeff_[i] << "x";
                    }
                    else {
                        std::cout << coeff_[i] << "x";
                    } 
                }
                else {
                    if(abs(coeff_[i]) < eps_) {
                        continue;
                    }
                    else if(coeff_[i] > 0) {
                        std::cout << "+" << coeff_[i] << "x^" << i;
                    }
                    else {
                        std::cout << coeff_[i] << "x^" << i;
                    }
                }    
            }

            std::cout << std::endl;
        }
    }

    friend Poly operator+(const Poly&, const Poly&);
    friend Poly operator-(const Poly&);
    friend Poly operator-(const Poly&, const Poly&);
    friend Poly operator*(const Poly&, const Poly&);
};

void test_poly();

class PolyWithSupp {
    Poly poly_;
    int start_;
    int end_;
    int N_;
public:
    PolyWithSupp(Poly poly, int start, int end, int N) : poly_(poly), start_(start), end_(end), N_(N) {
        if (N % 2 == 1) error(-1, "N is odd");

        start_ = std::max(start_, 0);
        end_ = std::min(end_, N_);
    };

    PolyWithSupp derivative() const {
        return PolyWithSupp(poly_.derivative(), start_, end_, N_);
    }

    double integrate(bool enable_k) {
        if (end_ - start_ == 0) {
            return 0;
        }
        else if (end_ - start_ == 1) {
            double k = 1;
            if (enable_k) {
                k = end_ <= N_ / 2 ? k1 : k2;
            }

            return k * poly_.integrate(static_cast<double>(start_) / N_, static_cast<double>(end_) / N_);
        }
        else if (end_ - start_ == 2) {
            auto p1 = PolyWithSupp(poly_, start_, end_ - 1, N_);
            auto p2 = PolyWithSupp(poly_, start_ + 1, end_, N_);

            return p1.integrate(enable_k) + p2.integrate(enable_k);
        }
        else {
            printf("start_: %d, end_: %d\n", start_, end_);
            error(-1, "supp is too big or bad");
        }
    }

    friend PolyWithSupp operator+(const PolyWithSupp&, const PolyWithSupp&);
    friend PolyWithSupp operator-(const PolyWithSupp&);
    friend PolyWithSupp operator-(const PolyWithSupp&, const PolyWithSupp&);
    friend PolyWithSupp operator*(const PolyWithSupp&, const PolyWithSupp&);
};

#endif