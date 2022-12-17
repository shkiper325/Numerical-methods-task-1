#include <iostream>

#include <cstdio> 

#include "compute_preparation.hpp"
#include "integrate.hpp"
#include "hat.hpp"
#include "computations.hpp"

using namespace std;

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

void main_routine(int K, int I, double min_val, double max_val) {

    // Определения

    int integrate_point_count = I;
    int solution_integrate_point_count = I;

    int n = K;
    const int solution_point_count = K;
    
    auto function = [](double x) -> double {return x;};

    // Вычисления

    cout << "Инициализация" << endl;

    auto a = gen_a(n);
    auto b = gen_b(n);
    auto c = gen_c(n);
    auto d = gen_d(n);
    auto e = gen_e(n);

    auto f = gen_f(n, integrate_point_count, function);

    cout << "Решение системы..." << endl;

    auto solution = solve_penta(a, b, c, d, e, f, n);

    // for(int i = 0; i < solution.size(); ++i) {
    //     printf("%9.3lf\n", solution(i));
    // }
    // printf("\n");

    // Обработка

    cout << "Подготовка выходного вектора..." << endl;

    VecD ret(solution_point_count, 0.);
    for(int pos = 0; pos < solution_point_count; ++pos) {
        double x = static_cast<double>(pos) / (solution_point_count - 1);

        for(int i = 0; i < 2 * n + 1; ++i) {
            double a = static_cast<double>(i / 2 - 1) / n + (i % 2 == 0 ? 0. : 1. / n);
            double b = static_cast<double>(i / 2 + 1) / n;

            double norm = 1; // integrate(a, b, solution_integrate_point_count, gen_hat(i, n));
            ret(pos) += solution(i) * gen_hat(i, n)(x) / norm;
        }
    }

    // // Вывод
    
    // for(int pos = 0; pos < solution_point_count; ++pos) {
    //     double x = static_cast<double>(pos) / (solution_point_count - 1);

    //     printf("%9.3lf: %9.3lf\n", x, ret(pos));
    // }

    // Запись в файл

    cout << "Запись в points.json" << endl;

    // xs

    auto fd = fopen("points.json", "w");

    fprintf(fd, "{\"x\" : [\n");

    for(int pos = 0; pos < solution_point_count; ++pos) {
        double x = static_cast<double>(pos) / (solution_point_count - 1);

        if (pos == solution_point_count - 1) {
            fprintf(fd, "    %9.6lf\n", x);
        } else {
            fprintf(fd, "    %9.6lf,\n", x);
        }
    }

    fprintf(fd, "],\n");

    // ys

    fprintf(fd, "\"y\" : [\n");

    for(int pos = 0; pos < solution_point_count; ++pos) {
        if (pos == solution_point_count - 1) {
            fprintf(fd, "    %9.3lf\n", min(max(ret(pos), min_val), max_val));
        } else {
            fprintf(fd, "    %9.3lf,\n", min(max(ret(pos), min_val), max_val));
        }
    }

    fprintf(fd, "]}\n");

    fclose(fd);

    cout << "Готово!" << endl;
}

int main(int argc, char* argv[]) {
    main_routine(stoi(argv[1]), stoi(argv[2]), -0.001, 0.001);

    return 0;
}