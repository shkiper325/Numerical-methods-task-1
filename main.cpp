#include <cstdio>

#include "compute_preparation.hpp"
#include "integrate.hpp"
#include "hat.hpp"
#include "computations.hpp"

void test_integrate() {
    printf("\nintegrate() test:\n");

    printf("1: %9.3lf\n", integrate(0, 0.5, 100, [](double) -> double {return 1;}));
    printf("x: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x;}));
    printf("x^2: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x;}));
    printf("x^3: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x * x;}));
}

void test_gen_f(int n, double x) {
    auto f = [](double x) -> double {
        return x * x;
    };

    auto b = gen_f(n, 100, f);

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

void test() {
    test_integrate();
    test_gen_f(100, 0.5);
}

void main_routine(int K, int I) {

    // Определения

    int integrate_point_count = I;
    int solution_integrate_point_count = I;

    int n = K;
    const int solution_point_count = K;
    
    auto function = [](double x) -> double {return x;};

    // Вычисления

    auto a = gen_a(n);
    auto b = gen_b(n);
    auto c = gen_c(n);
    auto d = gen_d(n);
    auto e = gen_e(n);

    auto f = gen_f(n, integrate_point_count, function);

    auto solution = solve_penta(a, b, c, d, e, f, n);

    // for(int i = 0; i < solution.size(); ++i) {
    //     printf("%9.3lf\n", solution(i));
    // }
    // printf("\n");

    // Обработка

    VecD ret(solution_point_count, 0.);
    for(int pos = 0; pos < solution_point_count; ++pos) {
        double x = static_cast<double>(pos) / (solution_point_count - 1);

        for(int i = 0; i < 2 * n + 1; ++i) {
            double a = static_cast<double>(i / 2 - 1) / n + (i % 2 == 0 ? 0. : 1. / n);
            double b = static_cast<double>(i / 2 + 1) / n;

            double norm = integrate(a, b, solution_integrate_point_count, gen_hat(i, n));
            ret(pos) += solution(i) * gen_hat(i, n)(x) / norm;
        }
    }

    // Вывод
    
    for(int pos = 0; pos < solution_point_count; ++pos) {
        double x = static_cast<double>(pos) / (solution_point_count - 1);

        printf("%9.3lf: %9.3lf\n", x, ret(pos));
    }
}

int main() {
    main_routine(1000, 100);

    return 0;
}