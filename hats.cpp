#include "Vec.hpp"
#include "error.hpp"
#include "hat.hpp"

double gen_hat(int i, int pos, int n) {
    if (n % 2 == 1) {
        error(-1, "Now can generate hats ony for even numbers");
    }

    if (i % 2 == 0) { //integrate with big
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
}