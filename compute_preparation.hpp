#ifndef COMPUTE_PREPARATION_HPP
#define COMPUTE_PREPARATION_HPP

#include <functional>

#include "Vec.hpp"

/*
  Создание правого столбца для СЛАУ из какой-то функции f.
  point_count - число точек сетки, по которой интегрируется
  интегрирования f и шапочки. В дальнейшем надо перейти к
  квадратурной формуле.
*/

VecD gen_f(int n, int point_count, std::function<double(double)> f);

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

VecD gen_a(int n);
VecD gen_b(int n);
VecD gen_c(int n);
VecD gen_d(int n);
VecD gen_e(int n);


#endif