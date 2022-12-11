#include "integrate.hpp"
#include "error.hpp"

double integrate(double a, double b, int n, double(*f)(double)) {
    if (n < 2) error(-1, "n < 2 in integrate");

    double h = (b - a) / (n - 1);
    double len = (b - a);

    double result = 0;
    for(int i = 0; i < (n - 1); ++i) {
        double x = h * (static_cast<double>(i) + 0.5);

        double val = f(x);
        result += val * len;
    }

    return result;
}