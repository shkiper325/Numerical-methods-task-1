#include <cstdio>

#include "compute_preparation.hpp"
#include "integrate.hpp"
#include "hat.hpp"

void test_integrate() {
    printf("\nintegrate() test:\n");

    printf("1: %9.3lf\n", integrate(0, 0.5, 100, [](double) -> double {return 1;}));
    printf("x: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x;}));
    printf("x^2: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x;}));
    printf("x^3: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x * x;}));
}

void test_gen_b(int n, double x) {
    auto f = [](double x) -> double {
        return x * x;
    };

    auto b = gen_b(n, 100, f);

    // printf("\n");
    // for(int i = 0; i < 2 * n + 1; ++i) {
    //     printf("b(%d): %9.6lf\n", i, b(i));
    // }

    double val = 0;

    for(int i = 0; i < 2 * n + 1; ++i) {
        double norm = integrate(static_cast<double>(i / 2 - 1) / n, static_cast<double>(i / 2 + 1) / n, 100, gen_hat(i, n));
        val += b(i) * gen_hat(i, n)(x) / norm;
    }

    printf("\nval: %9.6lf\n", val);
}

int main() {
    test_gen_b(6, 0.5);

    test_integrate();

    return 0;
}