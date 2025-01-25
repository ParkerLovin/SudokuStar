#!/usr/bin/python3
import tkinter as tk

solution_string = input()	# Get the solution from sudoku_solver.cpp
root = tk.Tk()	# Create GUI window.

# Create the grid and display the solution.
for row in range(9):
	for col in range(9):
		text_var = tk.StringVar()
		text_var.set(solution_string[row * 9 + col])
		cell = tk.Label(root, textvariable=text_var, font=("Arial", 50), padx=20, pady=2, justify="center", bd=1, relief="solid")
		cell.grid(row=row, column=col)
exit_button = tk.Button(root, text="Exit Program", command=root.destroy)	# Create exit button.
exit_button.grid(row = 10, columnspan=10)
root.title("Solution")

root.mainloop()
