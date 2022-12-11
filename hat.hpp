#ifndef HAT_HPP
#define HAT_HPP

#include <functional>

double gen_hats_scalar_product(int i, int pos, int n);

std::function<double(double)> big_hat(int i, int n);
std::function<double(double)> small_hat(int i, int n);

#endif