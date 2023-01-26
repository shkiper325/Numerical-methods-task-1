#include <functional>
#include <algorithm>

#include <cmath>

#include "Vec.hpp"
#include "error.hpp"
#include "hat.hpp"

using namespace std;

double gen_hats_scalar_product(int i, int pos, int n) {
    if (n % 2 == 1) {
        error(-1, "Now can generate hats ony for even numbers");
    }

    if (i % 2 == 0) { //integrate with big
        i /= 2;

        switch (pos) {
        case -2:
            if (i == 0) return 0;
            else if (i <= n / 2) return 11. / (30. * n) + 2. * n;
            else return 11. / (30. * n) + 8. * n / 3.;
        case -1:
            if (i == 0) return 0;
            else if (i <= n / 2) return 7. / (15. * n) + 8. * n;
            else return 7. / (15. * n) + 32. * n / 3.;
        case 0:
            if (i == 0) return 8. / (15. * n) + 2. * n;
            else if (i <= n / 2 - 1) return 16. / (15. * n) + 4. * n;
            else if (i == n / 2) return 16. / (15. * n) + 14. * n / 3.;
            else if (i < n) return 16. / (15. * n) + 16. * n / 3.;
            else return 8. / (15. * n) + 8. * n / 3.;
        case 1:
            if (i <= n / 2 - 1) return 7. / (15. * n) + 8. * n;
            else if (i < n) return 7. / (15. * n) + 32. * n / 3.;
            else return 0;
        case 2:
            if (i <= n / 2 - 1) return 11. / (30. * n) + 2. * n;
            else if (i < n) return 11. / (30. * n) + 8. * n / 3.;
            else return 0;
        default:
            error(-1, "bad pos given in get_hat");
        }
    } else {
        i /= 2;

        switch (pos) {
        case -2:
            return 0;
        case -1:
            if (i <= n / 2 - 1) return 7. / (15. * n) + 2. * n;
            else if (i < n) return 7. / (15. * n) + 8. * n / 3.;
            else return 0;
        case 0:
            if (i <= n / 2 - 1) return 8. / (15. * n) + 8. * n;
            else if (i < n) return 8. / (15. * n) + 32. * n / 3.;
            else return 0;
        case 1:
            if (i <= n / 2 - 1) return 7. / (15. * n) + 2. * n;
            else if (i < n) return 7. / (15. * n) + 8. * n / 3.;
            else return 0;
        case 2:
            return 0;
        default:
            error(-1, "bad pos given in get_hat");
        }
    }

    error(-1, "reached end of gen_hats_scalar_product");
    std::exit(-1);
}

// double gen_hats_scalar_product(int i, int pos, int n) {
//     if (n % 2 == 1) {
//         error(-1, "Now can generate hats ony for even numbers");
//     }

//     if (i % 2 == 0) { //integrate with big
//         switch (pos) {
//         case -2:
//             if (i == 0) return 0;
//             else if (i <= n / 2) return 11. / (30. * n) + 2. * n;
//             else return 11. / (30. * n) + 8. * n / 3.;
//         case -1:
//             if (i == 0) return 0;
//             else if (i <= n / 2) return 7. / (15. * n) + 8. * n;
//             else return 7. / (15. * n) + 32. * n / 3.;
//         case 0:
//             if (i == 0) return 8. / (15. * n) + 2. * n;
//             else if (i <= n / 2 - 1) return 16. / (15. * n) + 4. * n;
//             else if (i == n / 2) return 16. / (15. * n) + 14. * n / 3.;
//             else if (i < n) return 16. / (15. * n) + 16. * n / 3.;
//             else return 8. / (15. * n) + 8. * n / 3.;
//         case 1:
//             if (i <= n / 2 - 1) return 7. / (15. * n) + 8. * n;
//             else if (i < n) return 7. / (15. * n) + 32. * n / 3.;
//             else return 0;
//         case 2:
//             if (i <= n / 2 - 1) return 11. / (30. * n) + 2. * n;
//             else if (i < n) return 11. / (30. * n) + 8. * n / 3.;
//             else return 0;
//         default:
//             error(-1, "bad pos given in get_hat");
//         }
//     } else {
//         switch (pos) {
//         case -2:
//             return 0;
//         case -1:
//             if (i <= n / 2 - 1) return 7. / (15. * n) + 2. * n;
//             else if (i < n) return 7. / (15. * n) + 8. * n / 3.;
//             else return 0;
//         case 0:
//             if (i <= n / 2 - 1) return 8. / (15. * n) + 8. * n;
//             else if (i < n) return 8. / (15. * n) + 32. * n / 3.;
//             else return 0;
//         case 1:
//             if (i <= n / 2 - 1) return 7. / (15. * n) + 2. * n;
//             else if (i < n) return 7. / (15. * n) + 8. * n / 3.;
//             else return 0;
//         case 2:
//             return 0;
//         default:
//             error(-1, "bad pos given in get_hat");
//         }
//     }

//     error(-1, "reached end of gen_hats_scalar_product");
//     exit(-1);
// }

function<double(double)> big_hat(int i, int n) {
    return [n = n, i = i](double x) -> double {
        double left = max(0., static_cast<double>(i - 1) / n);
        double right = min(1., static_cast<double>(i + 1) / n);

        if (x < left || x > right) return 0;
        else return -pow(static_cast<double>(n) * (x - static_cast<double>(i) / n), 2) + 1.;
    };
}

function<double(double)> small_hat(int i, int n) {
    return [n = n, i = i](double x) -> double {
        double left = max(0., static_cast<double>(i) / n);
        double right = min(1., static_cast<double>(i + 1) / n);

        if (x < left || x > right) return 0;
        else return -pow(2. * static_cast<double>(n) * (x - (static_cast<double>(i) + 0.5) / n), 2) + 1.;
    };
}

function<double(double)> gen_hat(int i, int n) {
    if (i % 2 == 0) return big_hat(i / 2, n);
    else return small_hat(i / 2, n);
}