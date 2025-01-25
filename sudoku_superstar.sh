#!/bin/bash
g++ sudoku_solver.cpp -o sudoku_solver
chmod +x sudoku_solver
python3 input_gui.py | ./sudoku_solver | python3 solution_gui.py
