#include <functional>

#include "integrate.hpp"
#include "error.hpp"

using namespace std;

// double integrate(double a, double b, int n, function<double(double)> f) {
//     if (n < 2) error(-1, "n < 2 in integrate");

//     double h = (b - a) / (n - 1);

//     double result = 0;
//     for(int i = 0; i < (n - 1); ++i) {
//         double x = a + h * (static_cast<double>(i) + 0.5);

//         double val = f(x);
//         result += val * h;
//     }

//     return result;
// }

double integrate(double a, double b, int, function<double(double)> f) {
    return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
}

// double integrate(double a, double b, int n, function<double(double)> f) {
//     if (n < 2) error(-1, "n < 2 in integrate");

//     double h = (b - a) / (n - 1);

//     double result = 0;
//     for(int i = 0; i < (n - 1); ++i) {
//         double x = a + h * (static_cast<double>(i) + 0.5);

//         auto u = a + h * (static_cast<double>(i));
//         auto w = a + h * (static_cast<double>(i) + 1);

//         result += h / 6 * (f(u) + 4 * f((u + w) / 2) + f(w));
//     }

//     return result;
// }