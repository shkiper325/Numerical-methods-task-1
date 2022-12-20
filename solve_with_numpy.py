#!/usr/bin/env python

import numpy as np
import json

N = 100

TO_BE_PRINTED = False

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

def check(vals):
    h = 1 / (N - 1)

    C_dist = 0
    for i in range(1, N - 1):
        d1 = (vals[i - 1] - 2 * vals[i] + vals[i + 1]) / h / h


def main():
    fd = open('A.txt', 'r')
    A = np.array(list(map(np.double, fd.read().split('\n')[:-1]))).reshape((2 * N + 1, 2 * N + 1))
    fd.close()

    A[-1] = np.zeros(shape=(2 * N + 1,))
    A[0] = np.zeros(shape=(2 * N + 1,))
    A[-1, -1] = 1 #A[-2, -2]
    A[0, 0] = 1 #A[1, 1]

    fd = open('b.txt', 'r')
    b = np.array(list(map(np.double, fd.read().split('\n')[:-1])))
    fd.close()

    b[0] = 0
    b[-1] = 0

    if TO_BE_PRINTED:
        with np.printoptions(precision=3, suppress=True):
            for line in A:
                for val in line:
                    print(str(val).rjust(8), end=' ')
                print()

    sol = np.linalg.solve(A, b)

    result = []
    for i in range(N):
        x = i / (N - 1)

        val = 0
        for j in range(N + 1):
            val += fat_hat(j, N, x) * sol[2 * j]
            if j != N:
                val += small_hat(j, N, x) * sol[2 * j + 1]
        
        result.append(val)


    json_to_write = json.dumps({
        'x' : [i / (N - 1) for i in range(N)],
        'y' : list(result)
    })

    fd = open('points.json', 'w')
    fd.write(json_to_write)
    fd.close()

if __name__ == '__main__':
    main()