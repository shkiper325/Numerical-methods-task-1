#!/usr/bin/env bash

echo "Сборка..."
./build.bash
echo "100"
./main 100 10000
./solve_with_python.py
echo "200"
./main 200 10000
./solve_with_python.py
echo "400"
./main 400 10000
./solve_with_python.py
echo "800"
./main 800 10000
./solve_with_python.py
echo "1600"
./main 1600 10000
./solve_with_python.py