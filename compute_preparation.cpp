#include <iostream>

#include "compute_preparation.hpp"
#include "Vec.hpp"
#include "integrate.hpp"
#include "hats.hpp"
#include "error.hpp"

using namespace std;

/*
  Создание правого столбца для СЛАУ из какой-то функции f.
  point_count - число точек сетки, по которой интегрируется
  интегрирования f и шапочки. В дальнейшем надо перейти к
  квадратурной формуле.
*/


VecD gen_f(int n, int point_count, std::function<double(double)> f) {
    if (n % 2 == 1) {
        error(-1, "Now can generate b ony for even numbers");
    }

    VecD ret(2 * n + 1);
    
    for(int i = 0; i < 2 * n + 1; ++i) {
        double norm = 1; // get_norm(i, n);

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

/*
  Генерируют строки для пентадиагональной матрицы.
  Порядок строк:

  b
  a
  d
  c
  e

  Такой порядок нужен, чтобы работал решатель пентадиагональной системы.
  (решатель пока не работает)
*/

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