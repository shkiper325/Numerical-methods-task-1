#!/usr/bin/env python

import json

import numpy as np
import pentapy as pp

TO_BE_PRINTED = False

def integrate(f, a, b, point_count):
    h = (b - a) / (point_count - 1)

    x = a
    result = 0
    for i in range(point_count - 1):
        result += (f(x + h) + f(x)) / 2 * h
        x += h

    return result

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
        # hat = lambda x: fat_hat(j, N, x) * fat_hat(j, N, x)
        # norm = integrate(hat, (j - 1) / N, (j + 1) / N, 100)
        # norm = np.sqrt(norm)
        val += fat_hat(j, N, x) * sol[2 * j] / N # / norm #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for j in range(N):
        # hat = lambda x: small_hat(j, N, x) * small_hat(j, N, x)
        # norm = integrate(hat, (j - 1) / N, (j + 1) / N, 100)
        # norm = np.sqrt(norm)
        val += small_hat(j, N, x) * sol[2 * j + 1] / N # / norm #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    return val

def read_vec(path):
    fd = open(path, 'r')
    vec = np.array(list(map(np.double, fd.read().split('\n')[:-1])), dtype = np.double)
    fd.close()

    return vec

def solve_with_np():
    fd = open('b.txt', 'r')
    b = np.array(list(map(np.double, fd.read().split('\n')[:-1])))
    fd.close()

    b[0] = 0
    b[-1] = 0

    N = b.shape[0] // 2

    fd = open('A.txt', 'r')
    A = np.array(list(map(np.double, fd.read().split('\n')[:-1]))).reshape((2 * N + 1, 2 * N + 1))
    fd.close()

    A[-1] = np.zeros(shape=(2 * N + 1,))
    A[0] = np.zeros(shape=(2 * N + 1,))
    A[-1, -1] = 1
    A[0, 0] = 1

    if TO_BE_PRINTED:
        with np.printoptions(precision=3, suppress=True):
            for line in A:
                for val in line:
                    print(str(val).rjust(8), end=' ')
                print()

    sol = np.linalg.solve(A, b)

    print('Error:', np.amax(np.abs((A @ sol) - b)))

    return sol, N

def solve_with_penta():
    d_2 = read_vec('d_2.txt')
    d_1 = read_vec('d_1.txt')
    d_0 = read_vec('d_0.txt')
    d_minus1 = read_vec('d_minus1.txt')
    d_minus2 = read_vec('d_minus2.txt')

    N = d_2.shape[0] // 2

    d_0[0] = 1
    d_1[0] = 0
    d_2[0] = 0

    d_0[-1] = 1
    d_minus1[-1] = 0
    d_minus2[-1] = 0

    b = read_vec('b.txt')

    b[0] = 0
    b[-1] = 0

    M = np.stack([d_2, d_1, d_0, d_minus1, d_minus2], axis = 0)
    #print(M)

    sol = pp.solve(M, b, is_flat=True)

    #print(sol)

    return sol, N

def exact(x):
    if x <=  0.5:
        return x - 1.11102 * np.sinh(0.816497 * x)
    else:
        return 0.159194 * (
                           6.28166 * x
                           +1.41421 * np.cosh(0.235702 * (4.73205 - 3. * x)) 
                           -3.35747 * np.cosh(0.353553 * (1. - 2. * x))
                           -1.41421 * np.cosh(0.235702 * (-1.26795 + 3. * x))
                           +7.51362 * np.sinh(0.353553 * (1. - 2. * x))
        )

def main():
    sol, N = solve_with_penta()

    result = []
    for i in range(N + 1):
        x = i / N

        result.append(np.abs(eval_result(x, sol) - exact(x)))

    print('Max error:', np.amax(result))

    print('Solution in 1/2:', eval_result(0.5, sol))
    print('Solution in 3/4:', eval_result(0.75, sol))

    json_to_write = json.dumps({
        'x' : [i / N for i in range(N + 1)],
        'y' : list(result)
    })

    fd = open('points.json', 'w')
    fd.write(json_to_write)
    fd.close()

if __name__ == '__main__':
    main()