#!/bin/bash

g++ *.cpp -O3 -o main

echo "N = 50:"
./main 50 "$1"
./solve_with_python.py

echo "N = 100:"
./main 100 "$1"
./solve_with_python.py

echo "N = 200:"
./main 200 "$1"
./solve_with_python.py

echo "N = 400:"
./main 400 "$1"
./solve_with_python.py

./plot.py
