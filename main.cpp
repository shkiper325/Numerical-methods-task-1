#include <cstdio>

#include "compute_preparation.hpp"

void test_gen_b(int n) {
    auto f = [](double x) -> double {
        return x * x;
    };

    auto vec = gen_b(n, 100, f);

    for(int i = 0; i < 2 * n - 1; ++i) {
        printf("% 9.3lf\n", vec(i));
    }
}

int main() {
    test_gen_b(5);

    return 0;
}