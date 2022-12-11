#ifndef INTEGRATE_HPP
#define INTEGRATE_HPP

#include <functional>

double integrate(double a, double b, int n, std::function<double(double)> f);

#endif