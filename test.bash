#!/bin/bash

g++ *.cpp -O3 -o main

echo "N = 100:"
./main 100 100
./solve_with_python.py

echo "N = 200:"
./main 200 100
./solve_with_python.py

echo "N = 400:"
./main 400 100
./solve_with_python.py

echo "N = 800:"
./main 800 100
./solve_with_python.py

echo "N = 1600:"
./main 1600 100
./solve_with_python.py

echo "N = 3200:"
./main 3200 100
./solve_with_python.py

./plot.py