#!/usr/bin/env python

import json

import matplotlib
import matplotlib.pyplot as plt

def main():
    fd = open('left.json', 'r')
    text = fd.read()
    fd.close()

    parsed = json.loads(text)

    plt.figure(figsize=(15, 10), dpi=80)

    plt.plot(parsed['x'][2:-2], parsed['y'][2:-2])

    plt.xlabel('x')
    plt.ylabel('y')

    plt.savefig('plot.png')

if __name__ == '__main__':
    main()