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


    plt.figure(figsize=(25, 20), dpi=100)

    plt.plot(parsed['x'], parsed['y_computed'], color='blue')
    plt.plot(parsed['x'], parsed['y_target'], color='orange')

    plt.xlabel('x')
    plt.ylabel('y')

    plt.savefig('plot.png')

if __name__ == '__main__':
    main()