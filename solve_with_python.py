#!/usr/bin/env python

import json

import numpy as np
import pentapy as pp

TO_BE_PRINTED = True

def fat_hat(i, n, x):
    left = max(0, (i - 1) / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(n * (x - i / n)) ** 2 + 1

def small_hat(i, n, x):
    left = max(0, i / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(2 * n * (x - (i + 0.5) / n)) ** 2 + 1

def eval_result(x, sol):
    N = sol.shape[0] // 2

    val = 0
    for j in range(N + 1):
        val += fat_hat(j, N, x) * sol[2 * j]
    for j in range(N):
        val += small_hat(j, N, x) * sol[2 * j + 1]

    return val

def derivative(vals, h):
    ret = [None for i in range(len(vals))]

    ret[0] = (vals[1] - vals[0]) / h
    for i in range(1, len(vals) - 1): 
        ret[i] = (vals[i + 1] - vals[i - 1]) / (2 * h)
    ret[-1] = (vals[-1] - vals[-2]) / h

    return ret

def second_derivative(vals, h):
    ret = [None for i in range(len(vals))]

    ret[0] = (vals[2] - 2 * vals[1] + vals[0]) / (h * h)
    for i in range(1, len(vals) - 1): 
        ret[i] = (vals[i + 1] - 2 * vals[i] + vals[i - 1]) / (h * h)
    ret[-1] = (vals[-1] - 2 * vals[-2] + vals[-3]) / (h * h)

    return ret

def read_vec(path):
    fd = open(path, 'r')
    vec = np.array(list(map(np.double, fd.read().split('\n')[:-1])), dtype = np.double)
    fd.close()

    return vec

def solve_with_penta():
    a = np.concatenate([read_vec('tmp/a.txt'), [0, 0]], axis=0)
    b = np.concatenate([read_vec('tmp/b.txt'), [0]], axis = 0)
    c = read_vec('tmp/c.txt')
    d = np.concatenate([[0], read_vec('tmp/d.txt')], axis=0)
    e = np.concatenate([[0, 0], read_vec('tmp/e.txt')], axis=0)

    N = c.shape[0] // 2

    f = read_vec('tmp/f.txt')

    M = np.stack([a, b, c, d, e], axis = 0)

    sol = pp.solve(M, f, is_flat=True, solver=1)

    return sol, N

def transform(s):
    return np.array(list(map(float, s.split(' '))))

def solve_with_penta_for_Liza():
    a = transform('20 0 -6.63 0 -6.63 0 -6.63 0 -6.63 0 -6.63 0 -9.96333 0 -9.96333 0 -9.96333 0 -9.96333 0 0')
    b = transform('40 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 0')
    c = transform('1 53.3867 26.7733 53.3867 26.7733 53.3867 26.7733 53.3867 26.7733 53.3867 26.7733 80.0533 40.1067 80.0533 40.1067 80.0533 40.1067 80.0533 40.1067 80.0533 1')
    d = transform('0 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 13.38 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 20.0467 0')
    e = transform('0 0 -6.63 0 -6.63 0 -6.63 0 -6.63 0 -6.63 0 -9.96333 0 -9.96333 0 -9.96333 0 -9.96333 0 0')

    N = 10

    f = transform('0 0 0.0133111 0.00665556 0.0264892 0.0132446 0.0394027 0.0197013 0.0519224 0.0259612 0.0639234 0.0319617 0.0752857 0.0376428 0.0858957 0.0429478 0.0956475 0.0478237 0.104444 0.0522218 0')

    M = np.stack([a, b, c, d, e], axis = 0)

    sol = pp.solve(M, f, is_flat=True, solver=2)

    # mat = np.zeros(shape=(2 * N + 1, 2 * N + 1), dtype=np.float32)
    # for i in range(2 * N - 1):
    #     mat[i, i + 2] = a[i]
    # for i in range(2 * N):
    #     mat[i, i + 1] = b[i]
    # for i in range(2 * N + 1):
    #     mat[i, i] = c[i]
    # for i in range(1, 2 * N):
    #     mat[i, i - 1] = d[i]
    # for i in range(2, 2 * N - 1):
    #     mat[i, i - 2] = e[i]
    # np.savetxt('tmp/mat.txt', mat, fmt='%10.5f  ')

    # sol = np.linalg.solve(mat, f)

    return sol, N

def exact_solution(x):
    if x <= 0.5:
        return (-0.11188827105317398*(-17.620948696259987 + 15.833750602588106*2.718281828459045**(1.632993161855452*x) + 1.1368121458890366*2.718281828459045**(0.7071067811865475 + 1.632993161855452*x) - 3.114156287926125*2.718281828459045**(0.7618016810571369 + 1.632993161855452*x) + 0.5505102572168221*2.718281828459045**(1.1153550716504106 + 1.632993161855452*x) - 0.5505102572168221*2.718281828459045**(0.4082482904638631*(1. + 4.*x)) - 2.0650153761645464*2.718281828459045**(0.7071067811865475 + 0.816496580927726*x)*x + 2.905547372312596*2.718281828459045**(1.5236033621142735 + 0.816496580927726*x)*x - 28.761953832863615*2.718281828459045**(0.816496580927726*x)*x + 0.208608915613528*2.718281828459045**(0.816496580927726*(1. + x))*x))/2.718281828459045**(0.1178511301977579*(6.464101615137754 + 6.928203230275509*x))
    else:
        return (-0.11188827105317398*(-26.513559170900876 + 5.449489742783178*2.718281828459045**(1.4142135623730951*x) + 14.696938456699067*2.718281828459045**(0.4082482904638631 + 1.4142135623730951*x) - 0.5505102572168221*2.718281828459045**(0.816496580927726 + 1.4142135623730951*x) - 2.905547372312596*2.718281828459045**(1.1700499715209998 + 1.4142135623730951*x) + 2.0650153761645464*2.718281828459045**(0.35355339059327373*(1. + 4.*x))))/2.718281828459045**(0.2357022603955158*(4.732050807568877 + 3.*x)) + x

def main():
    sol, N = solve_with_penta()

    result = []
    errors = []
    l2_errors = []
    for i in range(N + 1):
        x = i / N

        result.append(eval_result(x, sol))
        errors.append(np.abs(eval_result(x, sol) - exact_solution(x)))
        l2_errors.append((eval_result(x, sol) - exact_solution(x)) ** 2)
    
    print('C-dist:', np.amax(errors))
    print('L2-dist:', np.sqrt(np.sum(l2_errors) / N))

    json_to_write = json.dumps({
        'x' : [i / N for i in range(N + 1)],
        'y_computed' : list(result),
        'y_target' : [exact_solution(i / N) for i in range(N + 1)]
    })

    fd = open('tmp/points.json', 'w')
    fd.write(json_to_write)
    fd.close()

    # second_der = np.array(second_derivative(result, 1 / N))
    # left = [(-1.5 if i <= (N + 1) / 2 else -2) * second_der[i] + result[i] for i in range(N + 1)]

    # json_to_write = json.dumps({
    #     'x' : [i / N for i in range(N + 1)],
    #     'y' : list(left)
    # })

    # fd = open('tmp/left.json', 'w')
    # fd.write(json_to_write)
    # fd.close()

if __name__ == '__main__':
    main()