#!/usr/bin/env python

import numpy as np

def main():
    A = np.array([
                    [  1,  2,  3,  0,  0,  0,  0],
                    [  4,  5,  6,  7,  0,  0,  0],
                    [  8,  9, 10, 11, 12,  0,  0],
                    [  0, 13, 14, 15, 16, 17,  0],
                    [  0,  0, 18, 19, 20, 21, 22],
                    [  0,  0,  0, 23, 24, 25, 26],
                    [  0,  0,  0,  0, 27, 28, 29]
                 ],
                 dtype = np.double)

    b = np.array([-5, -6, -7, -8, -9, -10, -11], dtype = np.double)
    
    x = np.linalg.solve(A, b)

    print(x)

if __name__ == '__main__':
    main()