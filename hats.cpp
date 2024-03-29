#include <functional>
#include <algorithm>

#include <cmath>

#include "Poly.hpp"
#include "error.hpp"
#include "calculus.hpp"

using namespace std;

const double k1 = 1.5;
const double k2 = 2;

/*
    Функция, возвращяющая функцию, которая реализует
    большую шапочку с центром i при сетке с точками
    [0..n]
*/

function<double(double)> functional_big_hat(int i, int N) {
    return [N = N, i = i](double x) -> double {
        double left = max(0., static_cast<double>(i - 1) / N);
        double right = min(1., static_cast<double>(i + 1) / N);

        if (x < left || x > right) return 0;
        else return -pow(static_cast<double>(N) * (x - static_cast<double>(i) / N), 2) + 1.;
    };
}

/*
    Функция, возвраляющая функцию, которая реализует
    маленькую шапочку с левым концом i при сетке с точками
    [0..n]
*/

function<double(double)> functional_small_hat(int i, int N) {
    return [N = N, i = i](double x) -> double {
        double left = max(0., static_cast<double>(i) / N);
        double right = min(1., static_cast<double>(i + 1) / N);

        if (x < left || x > right) return 0;
        else return -pow(2. * static_cast<double>(N) * (x - (static_cast<double>(i) + 0.5) / N), 2) + 1.;
    };
}

function<double(double)> functional_hat(int k, int n) {
    if (k % 2 == 0) return functional_big_hat(k / 2, n);
    else return functional_small_hat(k / 2, n);
}

/*
    Аналоги функций выше, реализованные как многочлены
*/

Poly poly_big_hat(int i, int N) {
    double a = -N * N;
    double b = 2 * i * N;
    double c = 1 - i * i;

    return Poly({c, b, a});
}

Poly poly_small_hat(int i, int N) {
    double a = -4 * N * N;
    double b = 4 * N + 8 * i * N;
    double c = -4 * i - 4 * i * i;

    return Poly({c, b, a});
}

PolyWithSupp poly_hat(int k, int N) {
    if (k % 2 == 0) return PolyWithSupp(poly_big_hat(k / 2, N), k / 2 - 1, k / 2 + 1, N);
    else return PolyWithSupp(poly_small_hat(k / 2, N), k / 2, k / 2 + 1, N);
}

vector<vector<double> >gen_diag(int N) {
    // if (N % 2 == 1) error(-1, "N is odd");
    // if (N < 100) error(-1, "N < 100");

    vector<double> a(2 * N - 1);
    vector<double> b(2 * N);
    vector<double> c(2 * N + 1);
    vector<double> d(2 * N);
    vector<double> e(2 * N - 1);

    for(int k = 0; k < 2 * N + 1; ++k) {
        if (k <= 2 * N - 2) {
            PolyWithSupp main_hat = poly_hat(k, N);
            PolyWithSupp sub_hat = poly_hat(k + 2, N);

            a[k] = (main_hat.derivative() * sub_hat.derivative()).integrate(true) + (main_hat * sub_hat).integrate(false);
        }

        if (k <= 2 * N - 1) {
            PolyWithSupp main_hat = poly_hat(k, N);
            PolyWithSupp sub_hat = poly_hat(k + 1, N);

            b[k] = (main_hat.derivative() * sub_hat.derivative()).integrate(true) + (main_hat * sub_hat).integrate(false);
        }

        {
            PolyWithSupp main_hat = poly_hat(k, N);
            PolyWithSupp sub_hat = poly_hat(k, N);

            c[k] = (main_hat.derivative() * sub_hat.derivative()).integrate(true) + (main_hat * sub_hat).integrate(false);
        }

        if (k >= 1) {
            PolyWithSupp main_hat = poly_hat(k, N);
            PolyWithSupp sub_hat = poly_hat(k - 1, N);

            d[k - 1] = (main_hat.derivative() * sub_hat.derivative()).integrate(true) + (main_hat * sub_hat).integrate(false);
        }

        if (k >= 2) {
            PolyWithSupp main_hat = poly_hat(k, N);
            PolyWithSupp sub_hat = poly_hat(k - 2, N);

            e[k - 2] = (main_hat.derivative() * sub_hat.derivative()).integrate(true) + (main_hat * sub_hat).integrate(false);
        }
    }

    return {a, b, c, d, e};
}

vector<double> gen_f(int N, int point_count, std::function<double(double)> f) {
    // if (N % 2 == 1) {
    //     error(-1, "Now can generate b ony for even numbers");
    // }

    vector<double> ret(2 * N + 1);
    
    for(int k = 0; k < 2 * N + 1; ++k) {
        double a = static_cast<double>(k / 2 - 1) / N + (k % 2 == 0 ? 0. : 1. / N);
        double b = static_cast<double>(k / 2 + 1) / N;

        // ret[k] = (poly_hat(k, N) * PolyWithSupp(Poly({0, 1}), 0, N, N)).integrate(false);

        auto hat = functional_hat(k, N);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret[k] = integrate(a, b, point_count, multilpied);
    }
    
    return ret;
}

vector<vector<double> > set_initial_cond(vector<vector<double> > diag, vector<double> f) {
    auto a = diag[0];
    auto b = diag[1];
    auto c = diag[2];
    auto d = diag[3];
    auto e = diag[4];

    int N = c.size() / 2;

    c[0] = 1;
    b[0] = 4 * N;
    a[0] = 2 * N;
    f[0] = 0;
    
    e[2 * N - 2] = 0;
    d[2 * N - 1] = 0;
    c[2 * N] = 1;
    f[2 * N] = 0;

    return {a, b, c, d, e, f};
}