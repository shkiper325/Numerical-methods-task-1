#ifndef COMPUTE_PREPARATION_HPP
#define COMPUTE_PREPARATION_HPP

#include <functional>

#include "Vec.hpp"

VecD gen_f(int n, int point_count, std::function<double(double)> f);

VecD gen_a(int n);
VecD gen_b(int n);
VecD gen_c(int n);
VecD gen_d(int n);
VecD gen_e(int n);


#endif