#ifndef COMPUTE_PREPARATION_HPP
#define COMPUTE_PREPARATION_HPP

#include <functional>

#include "Vec.hpp"

VecD gen_f(int n, int point_count, std::function<double(double)> f);

#endif