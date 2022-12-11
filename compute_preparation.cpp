#include "compute_preparetion.hpp"
#include "Vec.hpp"
#include "integrate.hpp"
#include "hat.hpp"
#include "error.hpp"

VecD gen_b(int n, int point_count, std::function<double(double)> f) {
    if (n % 2 == 1) {
        error(-1, "Now can generate b ony for even numbers");
    }

    VecD ret(2 * n - 1);
    
    for(int j = 0; j < n; ++j) {
        auto hat = small_hat(j, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(2 * j) = integrate(static_cast<double>(j), static_cast<double>(j + 1), point_count, multilpied);
    }

    for (int j = 1; j < n; ++j) {
        auto hat = big_hat(j, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        ret(2 * j - 1) = integrate(static_cast<double>(j - 1), static_cast<double>(j + 1), point_count, multilpied);
    }

    return ret;
}