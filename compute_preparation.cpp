#include <iostream>

#include "compute_preparation.hpp"
#include "Vec.hpp"
#include "integrate.hpp"
#include "hats.hpp"
#include "error.hpp"

using namespace std;

double get_norm(int i, int n) {
    auto hat = gen_hat(i, n);

    auto hat_sq = [hat = hat](double x) -> double {return hat(x) * hat(x);};
    double norm = integrate(static_cast<double>(i / 2 - 1) / n, static_cast<double>(i / 2 + 1) / n, 100, hat_sq);
    norm = sqrt(norm);

    return norm;
}

VecD gen_f(int n, int point_count, std::function<double(double)> f) { //ALARM! разные границы для разных шапочек для асимптотики
    if (n % 2 == 1) {
        error(-1, "Now can generate b ony for even numbers");
    }

    VecD ret(2 * n + 1);
    
    for(int i = 0; i < 2 * n + 1; ++i) {
        double norm = get_norm(i, n);

        // double a = static_cast<double>(i / 2 - 1) / n + (i % 2 == 0 ? 0. : 1. / n);
        double a = static_cast<double>(i / 2 - 1) / n;
        double b = static_cast<double>(i / 2 + 1) / n;

        auto hat = gen_hat(i, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(i) = integrate(a, b, point_count, multilpied) / norm;
    }
    
    return ret;
}

VecD gen_e(int n) {
    VecD ret(2 * n + 1, 0.);

    for (int i = 2; i < 2 * n + 1; ++i) {
        ret(i) = gen_hats_scalar_product(i, -2, n);
    }

    return ret;
}

VecD gen_c(int n) {
    VecD ret(2 * n + 1, 0.);

    for (int i = 1; i < 2 * n + 1; ++i) {
        ret(i) = gen_hats_scalar_product(i, -1, n);
    }

    return ret;
}

VecD gen_d(int n) {
    VecD ret(2 * n + 1, 0.);

    for (int i = 0; i < 2 * n + 1; ++i) {
        ret(i) = gen_hats_scalar_product(i, 0, n);
    }

    return ret;
}

VecD gen_a(int n) {
    VecD ret(2 * n + 1, 0.);

    for (int i = 0; i < 2 * n; ++i) {
        ret(i) = gen_hats_scalar_product(i, 1, n);
    }

    return ret;
}

VecD gen_b(int n) {
    VecD ret(2 * n + 1, 0.);

    for (int i = 0; i < 2 * n - 1; ++i) {
        ret(i) = gen_hats_scalar_product(i, 2, n);
    }

    return ret;
}