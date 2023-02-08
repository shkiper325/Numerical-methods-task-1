#include <iostream>

#include <cstdio>
#include <cmath> 

#include "compute_preparation.hpp"
#include "integrate.hpp"
#include "hats.hpp"
#include "penta.hpp"

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
  Нерабочий тест, можно игнорировать
*/

// void test_gen_f(int n, double x) {
//     auto f = [](double x) -> double {
//         return x;
//     };

//     auto b = gen_f(n, 100, f);

//     // printf("\n");
//     // for(int i = 0; i < 2 * n + 1; ++i) {
//     //     printf("b(%d): %9.6lf\n", i, b(i));
//     // }

//     double val = 0;

//     for(int i = 0; i < 2 * n + 1; ++i) {
//         val += b(i) * gen_hat(i, n)(x);
//     }

//     printf("\nval: %9.6lf\n", val);
// }

/*
  Тест решателя пентадиагональной системы,
  решатель его пока не проходит
*/

void test_solve_penta() {
    double arr_a[] = {  2,  4, -1, -5, -2,  2,  0};
    VecD a(7, arr_a);

    double arr_b[] = {  3,  7,  2,  1, -4,  0,  0};
    VecD b(7, arr_b);

    double arr_c[] = {  0,  4,  2, -1,  2,  1,  1};
    VecD c(7, arr_c);

    double arr_d[] = {  1,  5,  3, -4,  3,  0,  3};
    VecD d(7, arr_d);

    double arr_e[] = {  0,  0, -1,  0,  1,  1,  2};
    VecD e(7, arr_e);

    double arr_f[] = { -5, -6, -7, -8, -9,-10,-11};
    VecD f(7, arr_f);

    printf("Solving...\n");
    auto solution = solve_penta(a, b, c, d, e, f, 7);

    printf("\nSolution for pentadiagional system:\n");
    for(int i = 0; i < 7; ++i) {
        printf(" %9.6lf\n", solution(i));
    }
}

/*
  Запись вектора в столбик в файл
*/

void dump_vec(VecD vec, string path) {
    auto fd = fopen(path.c_str(), "w");
    auto m = vec.size();

    for (int i = 0; i < m; ++i) {
        fprintf(fd, "%30.20e\n", vec(i));
    }

    fclose(fd);
}

void main_routine(int K, int I, double min_val, double max_val) {

    // Определения

    int integrate_point_count = I;
    int solution_integrate_point_count = I;

    int n = K;
    const int solution_point_count = K;
    
    auto function = [](double x) -> double {return x;}; 
    // auto function = [](double x) -> double {return x;}; 
    
    // Вычисления

    cout << "Инициализация" << endl;

    auto a = gen_a(n);
    auto b = gen_b(n);
    auto c = gen_c(n);
    auto d = gen_d(n);
    auto e = gen_e(n);

    auto f = gen_f(n, integrate_point_count, function);

    cout << "Запись системы в файлы..." << endl;

    // Запись в файл

    /*
      Для решателя СЛАУ в numpy
    */

    auto fd = fopen("A.txt", "w");

    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            double val;

            if (i == j + 2) val = e(i);
            else if (i == j + 1) val = c(i);
            else if (i == j) val = d(i);
            else if (i == j - 1) val = a(i);
            else if (i == j - 2) val = b(i);
            else val = 0;
 
            fprintf(fd, "%18.12e\n", val);
        }
    }

    fclose(fd);

    fd = fopen("b.txt", "w");

    for (int i = 0; i < 2 * n + 1; ++i) {
        fprintf(fd, "%18.12e\n", f(i));
    }

    fclose(fd);

    /*
      Для решателя в pentapy
    */

    dump_vec(b, "d_2.txt");
    dump_vec(a, "d_1.txt");
    dump_vec(d, "d_0.txt");
    dump_vec(c, "d_minus1.txt");
    dump_vec(e, "d_minus2.txt");

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
    // test_gen_f(10, 0.7);
    main_routine(stoi(argv[1]), stoi(argv[2]), -1, 1);

    return 0;
}