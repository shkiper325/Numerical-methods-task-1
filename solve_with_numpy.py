#!/usr/bin/env python

import json

import numpy as np
import pentapy as pp

TO_BE_PRINTED = False

"""
Простое численное интегрирование
"""
def integrate(f, a, b, point_count):
    h = (b - a) / (point_count - 1)

    x = a
    result = 0
    for i in range(point_count - 1):
        result += (f(x + h) + f(x)) / 2 * h
        x += h

    return result

"""
Реализация толестой шапочки
"""
def fat_hat(i, n, x):
    left = max(0, (i - 1) / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(n * (x - i / n)) ** 2 + 1

"""
Реализация тонкой шапочки
"""
def small_hat(i, n, x):
    left = max(0, i / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(2 * n * (x - (i + 0.5) / n)) ** 2 + 1

"""
Вычисление функции-решения ОДУ в точке x при условии, что при решении СЛАУ получились
коэффициенты sol (2 * n + 1 штук)
"""
def eval_result(x, sol):
    n = sol.shape[0] // 2

    val = 0
    for j in range(n + 1):
        # hat = lambda x: fat_hat(j, n, x) * fat_hat(j, n, x)
        # norm = integrate(hat, (j - 1) / n, (j + 1) / n, 100)
        # norm = np.sqrt(norm)
        val += fat_hat(j, n, x) * sol[2 * j]# / norm #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for j in range(n):
        # hat = lambda x: small_hat(j, n, x) * small_hat(j, n, x)
        # norm = integrate(hat, (j - 1) / n, (j + 1) / n, 100)
        # norm = np.sqrt(norm)
        val += small_hat(j, n, x) * sol[2 * j + 1] # / norm #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    return val

"""
Прочитать столбец из чисел с плавающей запятой
"""
def read_vec(path):
    fd = open(path, 'r')
    vec = np.array(list(map(np.double, fd.read().split('\n')[:-1])), dtype = np.double)
    fd.close()

    return vec

"""
Решить систему с помощью numpy
"""
def solve_with_np():
    fd = open('b.txt', 'r')
    b = np.array(list(map(np.double, fd.read().split('\n')[:-1])))
    fd.close()

    b[0] = 0
    b[-1] = 0

    n = b.shape[0] // 2

    fd = open('A.txt', 'r')
    A = np.array(list(map(np.double, fd.read().split('\n')[:-1]))).reshape((2 * n + 1, 2 * n + 1))
    fd.close()

    A[-1] = np.zeros(shape=(2 * n + 1,))
    A[0] = np.zeros(shape=(2 * n + 1,))
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

    return sol, n

"""
Решить систему с помощью pentapy
"""
def solve_with_penta():
    d_2 = read_vec('d_2.txt')
    d_1 = read_vec('d_1.txt')
    d_0 = read_vec('d_0.txt')
    d_minus1 = read_vec('d_minus1.txt')
    d_minus2 = read_vec('d_minus2.txt')

    n = d_2.shape[0] // 2

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

    return sol, n

"""
Точное решение
"""
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
    sol, n = solve_with_penta()

    result = []
    diffs = []
    for i in range(n + 1):
        x = i / n

        result.append(eval_result(x, sol))
        diffs.append(np.abs(eval_result(x, sol) - exact(x)))

    print('Max error:', np.amax(diffs))

    print('Solution in 1/2:', eval_result(0.5, sol))
    print('Solution in 3/4:', eval_result(0.75, sol))

    json_to_write = json.dumps({
        'x' : [i / n for i in range(n + 1)],
        'y' : list(result)
    })

    fd = open('points.json', 'w')
    fd.write(json_to_write)
    fd.close()

if __name__ == '__main__':
    main()