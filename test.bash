#!/bin/bash

g++ *.cpp -O3 -o main

echo "N = 101:"
./main 101 1000
./solve_with_python.py

echo "N = 200:"
./main 200 1000
./solve_with_python.py

echo "N = 403:"
./main 403 1000
./solve_with_python.py

echo "N = 800:"
./main 800 1000
./solve_with_python.py

./plot.py