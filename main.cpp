#include <iostream>
#include <vector>

#include <cstdio>
#include <cmath>

#include "calculus.hpp"
#include "hats.hpp"

using namespace std;

const double PI = 3.1416;

/*
    Тест для функции интегрирования
*/

void test_integrate() {
    printf("\nintegrate() test:\n");

    printf("1: %9.3lf\n", integrate(0, 0.5, 100, [](double) -> double {return 1;}));
    printf("x: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x;}));
    printf("x^2: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x;}));
    printf("x^3: %9.3lf\n", integrate(0, 0.5, 100, [](double x) -> double {return x * x * x;}));
}

/*
    Запись вектора в столбик в файл
*/

void dump_vec(vector<double> vec, string path) {
    auto fd = fopen(path.c_str(), "w");
    auto m = vec.size();

    for (int i = 0; i < m; ++i) {
        fprintf(fd, "%60.30e\n", vec[i]);
    }

    fclose(fd);
}

void main_routine(int N, int I) {

    // Определения

    auto function = [](double x) -> double {return x;}; 
    
    // Вычисления

    cout << "Инициализация" << endl;

    auto diags = gen_diag(N);
    auto f = gen_f(N, I, function);

    auto ready = set_initial_cond(diags, f);

    // Запись в файл

    cout << "Запись системы в файлы..." << endl;

    dump_vec(ready[0], "tmp/a.txt");
    dump_vec(ready[1], "tmp/b.txt");
    dump_vec(ready[2], "tmp/c.txt");
    dump_vec(ready[3], "tmp/d.txt");
    dump_vec(ready[4], "tmp/e.txt");
    dump_vec(ready[5], "tmp/f.txt");

    /*
      Решение линейной системы; пока что его надо запускать вручную в программах на python
      с даными, записанными в файлы выше.
    */
    
    // cout << "Решение системы..." << endl;

    // auto solution = solve_penta(a, b, c, d, e, f, n);

    // // Обработка

    // cout << "Подготовка выходного вектора..." << endl;

    // VecD ret(solution_point_count, 0.);
    // for(int pos = 0; pos < solution_point_count; ++pos) {
    //     double x = static_cast<double>(pos) / (solution_point_count - 1);

    //     for(int i = 0; i < 2 * n + 1; ++i) {
    //         double a = static_cast<double>(i / 2 - 1) / n + (i % 2 == 0 ? 0. : 1. / n);
    //         double b = static_cast<double>(i / 2 + 1) / n;

    //         double norm = integrate(a, b, solution_integrate_point_count, gen_hat(i, n));
    //         ret(pos) += solution(i) * gen_hat(i, n)(x) / norm;
    //     }
    // }

    // // Запись в файл

    // cout << "Запись в points.json" << endl;

    // // xs

    // fd = fopen("points.json", "w");

    // fprintf(fd, "{\"x\" : [\n");

    // for(int pos = 0; pos < solution_point_count; ++pos) {
    //     double x = static_cast<double>(pos) / (solution_point_count - 1);

    //     if (pos == solution_point_count - 1) {
    //         fprintf(fd, "    %9.6lf\n", x);
    //     } else {
    //         fprintf(fd, "    %9.6lf,\n", x);
    //     }
    // }

    // fprintf(fd, "],\n");

    // // ys

    // fprintf(fd, "\"y\" : [\n");

    // for(int pos = 0; pos < solution_point_count; ++pos) {
    //     if (pos == solution_point_count - 1) {
    //         fprintf(fd, "    %9.6lf\n", min(max(ret(pos), min_val), max_val));
    //     } else {
    //         fprintf(fd, "    %9.6lf,\n", min(max(ret(pos), min_val), max_val));
    //     }
    // }

    // fprintf(fd, "]}\n");

    // fclose(fd);

    cout << "Готово!" << endl;
}

int main(int argc, char* argv[]) {
    main_routine(stoi(argv[1]), stoi(argv[2]));

    return 0;
}