# SudokuSuperstar
This repository contains a program to solve sudoku problems.

## Usage
`./sudoku_superstar.sh`

This bash script will compile and run the necessary code to solve the sudoku problem. Immediately after running the bash script, you should see an image of a blank sudoku grid. Enter numbers into the grid to match the problem you wish to solve, then press "Save Grid." If the program is able to find a solution, it will display an updated grid with each square filled in correctly.

## Files
Please note that this program is only intended to be run through the provided bash script (sudoku_superstar.sh). This explanation is simply given to explain the purpose of each file.
### sudoku_superstar.sh
This file essentially links the other files and allows the user to enter only one short line to run the program.
### input_gui.py
This file opens a graphic interface so the user can enter their sudoku problem. Once they have saved the problem, the grid data is printed to the console for use by sudoku_solver.cpp.
### sudoku_solver.cpp
This file contains the actual solving logic. Upon finding a successful solution, the program prints it to the console to be displayed by solution_gui.py.
### solution_gui.py
This file reads the data from sudoku_solver.cpp and uses it to display the solution in grid form.
