#!/bin/bash

g++ *.cpp -O3 -o main

echo "N = 100:"
./main 100 "$1"
./solve_with_python.py

echo "N = 200:"
./main 200 "$1"
./solve_with_python.py

echo "N = 400:"
./main 400 "$1"
./solve_with_python.py

echo "N = 800:"
./main 800 "$1"
./solve_with_python.py

echo "N = 1600:"
./main 1600 "$1"
./solve_with_python.py

echo "N = 3200:"
./main 3200 "$1"
./solve_with_python.py

echo "N = 6400:"
./main 6400 "$1"
./solve_with_python.py

./plot.py