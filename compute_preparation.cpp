#include "compute_preparation.hpp"
#include "Vec.hpp"
#include "integrate.hpp"
#include "hat.hpp"
#include "error.hpp"

VecD gen_b(int n, int point_count, std::function<double(double)> f) {
    if (n % 2 == 1) {
        error(-1, "Now can generate b ony for even numbers");
    }

    VecD ret(2 * n + 1);
    
    for(int j = 0; j < n; ++j) {
        auto hat = small_hat(j, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(2 * j /**/+ 1) = integrate(static_cast<double>(j) / n, static_cast<double>(j + 1) / n, point_count, multilpied);
    }

    for (int j = 1; j < n; ++j) {
        auto hat = big_hat(j, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(2 * j - 1 /**/ + 1) = integrate(static_cast<double>(j - 1) / n, static_cast<double>(j + 1) / n, point_count, multilpied);
    }

    {
        auto hat = big_hat(0, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(0) = integrate(0.0, 1. / n, point_count, hat);
    }

    {
        auto hat = big_hat(n, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(2 * n) = integrate(1. - 1. / n, 1., point_count, hat);
    }
    
    return ret;
}