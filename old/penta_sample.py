#!/usr/bin/env python

import numpy as np

def main():
    A = np.array([
                    [  1,  2,  3,  0,  0,  0,  0],
                    [  4,  5,  4,  7,  0,  0,  0],
                    [ -1,  2,  3, -1,  2,  0,  0],
                    [  0,  0, -1, -4, -5,  1,  0],
                    [  0,  0,  1,  2,  3, -2, -4],
                    [  0,  0,  0,  1,  1,  0,  2],
                    [  0,  0,  0,  0,  2,  1,  3]
                 ],
                 dtype = np.double)

    b = np.array([-5, -6, -7, -8, -9, -10, -11], dtype = np.double)
    
    x = np.linalg.solve(A, b)

    print('Solution:', x)
    
    print('det:', np.linalg.det(A))

    print('Condition number:', np.linalg.cond(A))

    print('Check:', A @ x)

if __name__ == '__main__':
    main()