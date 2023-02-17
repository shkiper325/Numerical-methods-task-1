#!/usr/bin/env python

import json

import numpy as np

import matplotlib
import matplotlib.pyplot as plt

def main():
    fd = open('tmp/points.json', 'r')
    text = fd.read()
    fd.close()

    parsed = json.loads(text)

    plt.figure(figsize=(15, 10), dpi=80)

    y = np.array(parsed['y'])
    y = np.clip(y, -2, 2)

    plt.plot(parsed['x'], y)

    plt.xlabel('x')
    plt.ylabel('y')

    plt.savefig('plot.png')

if __name__ == '__main__':
    main()