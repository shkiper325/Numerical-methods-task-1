#include "compute_preparation.hpp"
#include "Vec.hpp"
#include "integrate.hpp"
#include "hat.hpp"
#include "error.hpp"

VecD gen_f(int n, int point_count, std::function<double(double)> f) { //ALARM! разные границы для разных шапочек для асимптотики
    if (n % 2 == 1) {
        error(-1, "Now can generate b ony for even numbers");
    }

    VecD ret(2 * n + 1);

    // printf("\n");
    
    for(int i = 0; i < 2 * n + 1; ++i) {
        auto hat = gen_hat(i, n);
        auto multilpied = [hat = hat, f = f](double x) -> double {
            return hat(x) * f(x);
        };

        double a = static_cast<double>(i / 2 - 1) / n + (i % 2 == 0 ? 0. : 1. / n);
        double b = static_cast<double>(i / 2 + 1) / n;

        // printf("left border: %9.3lf, right border: %9.3lf\n", a, b);
        // printf("values in [a, b]: %9.3lf %9.3lf %9.3lf %9.3lf %9.3lf\n",
        //        multilpied(a),
        //        multilpied(a + (b - a) / 4),
        //        multilpied(a + (b - a) / 2),
        //        multilpied(a + 3 * (b - a) / 4),
        //        multilpied(b)
        // );

        // printf("integrated: %9.3lf\n", integrate(a, b, point_count, multilpied));

        ret(i) = integrate(a, b, point_count, multilpied);
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