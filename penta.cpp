#include "penta.hpp"
#include "Vec.hpp"
#include <cstdio>

/*
  Пока нерабочий код
*/

VecD solve_penta(VecD a, VecD b, VecD c, VecD d, VecD e, VecD f, int n) {
    VecD mu(n, 0.), gamma(n, 0.), z(n, 0.), alpha(n - 1, 0.), beta(n - 2, 0.);

    // printf("a:\n");
    // a.print();
    // printf("b:\n");
    // b.print();
    // printf("c:\n");
    // c.print();
    // printf("d:\n");
    // d.print();
    // printf("e:\n");
    // e.print();
    // printf("f:\n");
    // f.print();

    mu(0) = d(0);
    alpha(0) = a(0) / mu(0);
    beta(0) = b(0) / mu(0);
    z(0) = f(0) / mu(0);

    gamma(1) = c(1);
    mu(1) = d(1) - alpha(0) * gamma(1);
    alpha(1) = (a(1) - beta(0) * gamma(1)) / mu(1);
    beta(1) = b(1) / mu(1);
    z(1) = (f(1) - z(0) * gamma(1)) / mu(1);

    for (int i = 2; i < n - 2; ++i) {
        gamma(i) = c(i) - alpha(i - 2) * e(i);
        mu(i) = d(i) - beta(i - 2) * e(i) - alpha(i - 1) * gamma(i);
        alpha(i) = (a(i) - beta(i - 1) * gamma(i)) / mu(i);
        beta(i) = b(i) / mu(i);
        z(i) = (f(i) - z(i - 2) * e(i) - z(i - 1) * gamma(i)) / mu(i);
    }

    gamma(n - 2) = c(n - 2) - alpha(n - 4) * e(n - 2);
    mu(n - 2) = d(n - 2) - beta(n - 4) * e(n - 2) - alpha(n - 3) * gamma(n - 2);
    alpha(n - 2) = (a(n - 2) - beta(n - 3) * gamma(n - 2)) / mu(n - 2);
    gamma(n - 1) = c(n - 1) - alpha(n - 3) * e(n - 1);
    mu(n - 1) = d(n - 1) - beta(n - 3) * e(n - 1) - alpha(n - 2) * gamma(n - 1);
    z(n - 2) = (f(n - 2) - z(n - 3) * e(n - 2) - z(n - 3) * gamma(n - 2)) / mu(n - 2);
    z(n - 1) = (f(n - 1) - z(n - 2) * e(n - 1) - z(n - 2) * gamma(n - 1)) / mu(n - 1);

    VecD ret(n);

    ret(n - 1) = z(n - 1);
    ret(n - 2) = z(n - 2) - alpha(n - 2) * ret(n - 1);

    for (int i = n - 3; i >= 0; --i) {
        ret(i) = z(i) - alpha(i) * ret(i + 1) - beta(i) * ret(i + 2);
    }

    return ret;
}