#include <algorithm>

#include "Poly.hpp"
#include "error.hpp"

using namespace std;

Poly operator+(const Poly& a, const Poly& b) {
    if(a.deg() == -1) return b;
    if(b.deg() == -1) return a;

    int d = max(a.deg(), b.deg());

    vector<double> result(d + 1);

    for(int i = 0; i < d + 1; ++i) {
        if (i <= a.deg() && i <= b.deg()) {
            result[i] = a.coeff_[i] + b.coeff_[i];
        } 
        else if (i > a.deg()) {
            result[i] = b.coeff_[i];
        }
        else {
            result[i] = a.coeff_[i];
        }
    }

    return Poly(result);
}

Poly operator-(const Poly& p) {
    vector<double> result(p.coeff_.size());

    for(int i = 0; i < result.size(); ++i) result[i] = -p.coeff_[i];

    return Poly(result);
}

Poly operator-(const Poly& a, const Poly& b) {
    return a + (-b);
}

Poly operator*(const Poly& a, const Poly& b) {
    if(a.deg() == -1 || b.deg() == -1) return Poly({0});

    vector<double> result(a.deg() + b.deg() + 1, 0);

    for(int i = 0; i < result.size(); ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j > a.deg() || (i - j) > b.deg()) continue;

            result[i] += a.coeff_[j] * b.coeff_[i - j];
        }
    }

    return Poly(result);
}

void test_poly() {
    Poly a({1, 2, -3, 4});
    Poly b({-5, 7, 8, 9, -19});
    Poly c({4, -5, 7, 8, 9, -2, -2});

    cout << "a: ";
    a.print();
    cout << endl;
    cout << "b: ";
    b.print();
    cout << endl;
    cout << "c: ";
    c.print();
    cout << endl;

    cout << "a * b - c: ";
    (a * b - c).print();
    cout << endl;

    cout << "Int[-5, 7](a * b - c): " << (a * b - c).integrate(-5, 7) << endl;
    cout << endl;

    cout << "a * b - c derivative: ";
    (a * b - c).derivative().print();
    cout << endl;
}

PolyWithSupp operator+(const PolyWithSupp& a, const PolyWithSupp& b) {
    if (a.N_ != b.N_) error(-1, "a.N_ != b.N_ in operator+");

    return PolyWithSupp(a.poly_ + b.poly_, max(a.start_, b.start_), min(a.end_, b.end_), a.N_);
}

PolyWithSupp operator-(const PolyWithSupp& p) {
    return PolyWithSupp(-p.poly_, p.start_, p.end_, p.N_);
}

PolyWithSupp operator-(const PolyWithSupp& a, const PolyWithSupp& b) {
    return a + (-b);
}
PolyWithSupp operator*(const PolyWithSupp& a, const PolyWithSupp& b) {
    if (a.N_ != b.N_) error(-1, "a.N_ != b.N_ in operator*");

    return PolyWithSupp(a.poly_ * b.poly_, max(a.start_, b.start_), min(a.end_, b.end_), a.N_);
}