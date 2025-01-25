#!/usr/bin/python3
import tkinter as tk

cells = []
master = tk.Tk()

def save_cells():	# TEMP
	cell_data = ""
	for cell in cells:
		content = cell.get()
		if not content in ["1", "2", "3", "4", "5", "6", "7", "8", "9", ""]:
			text_var = tk.StringVar()
			text_var.set("Error: please ensure that each square contains only one digit 1-9.")
			error_label = tk.Label(master, textvariable=text_var, fg="red")
			error_label.grid(row=11, columnspan=10)
			return
		else:
			if content == "":
				cell_data += " "
			else:
				cell_data += content
	print(cell_data.strip())
	master.destroy()
			
for row in range(9):
	for col in range(9):
		cell = tk.Entry(master, width=2, font=("Arial", 50), justify="center")
		cell.grid(row=row, column=col)
		cells.append(cell)
save_button = tk.Button(master, text="Save Grid", command=save_cells)
save_button.grid(row = 10, columnspan=10)
master.title("SudokuSuperstar")

master.mainloop()
