#!/usr/bin/env python

import json

import numpy as np

import matplotlib
import matplotlib.pyplot as plt

plt.rcParams.update({'font.size': 30})

def main():
    fd = open('tmp/points.json', 'r')
    text = fd.read()
    fd.close()

    parsed = json.loads(text)


    plt.figure(figsize=(15, 10), dpi=80)

    plt.plot(parsed['x'], parsed['y_computed'], color='blue')
    plt.plot(parsed['x'], parsed['y_target'], color='orange')

    plt.xlabel('x')
    plt.ylabel('u')

    plt.savefig('plot.png')

if __name__ == '__main__':
    main()