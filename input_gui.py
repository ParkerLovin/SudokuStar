#!/usr/bin/python3
import tkinter as tk

cells = []		# This list will hold tk.Entry objects representing grid squares.
root = tk.Tk()	# Create GUI window.

def save_cells():
	cell_data = ""	# String to hold cell data (number or blank) for output purposes.
	
	# For every cell, verify its contents. If invalid content is found, exit the function. If all content is valid, print the data and destroy the window.
	for cell in cells:
		content = cell.get()
		if not content in ["1", "2", "3", "4", "5", "6", "7", "8", "9", ""]:
			text_var = tk.StringVar()
			text_var.set("Error: please ensure that each square contains only one digit 1-9.")
			error_label = tk.Label(root, textvariable=text_var, fg="red")
			error_label.grid(row=11, columnspan=10)
			return
		else:
			if content == "":
				cell_data += " "
			else:
				cell_data += content
	print(cell_data)	# Print the cell data so it can be used by another program.
	root.destroy()

# Create the grid and save button for user input.			
for row in range(9):
	for col in range(9):
		cell = tk.Entry(root, width=2, font=("Arial", 50), justify="center")
		cell.grid(row=row, column=col)
		cells.append(cell)
save_button = tk.Button(root, text="Save Grid", command=save_cells)
save_button.grid(row = 10, columnspan=10)
root.title("SudokuSuperstar")

root.mainloop()
