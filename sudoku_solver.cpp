#include <iostream>
#include <string>
#include <tuple>
using namespace std;

//void print_grid(char* grid) {
//	for (int i = 0; i < 9; i++) {	// For every column
//		printf("-------------------");
//		printf("\n");
//		for (int j = 0; j < 9; j++) {	// Print every row
//			printf("|%c", grid[9 * i + j]);
//		}
//		printf("|");
//		printf("\n");
//	}
//	printf("-------------------\n\n\n");
//}

// The sudoku grid contains 9 3x3 squares. This function determines which of these squares contains
// a given point. The 3x3 squares are numbered left to right, then top to bottom as follows:
// 0 1 2
// 3 4 5
// 6 7 8
tuple<int, int> get_ninth(int row, int column) {
	if (row < 3) {
		if (column < 3) {
			return make_tuple(0, 0);
		} else if (column < 6) {
			return make_tuple(1, 0);
		} else {
			return make_tuple(2, 0);
		}
	} else if (row < 6) {
		if (column < 3) {
			return make_tuple(0, 1);
		} else if (column < 6) {
			return make_tuple(1, 1);
		} else {
			return make_tuple(2, 1);
		}
	} else {
		if (column < 3) {
			return make_tuple(0, 2);
		} else if (column < 6) {
			return make_tuple(1, 2);
		} else {
			return make_tuple(2, 2);
		}
	}
}

// Solves the puzzle by examining each empty space and narrowing the possible contents down to one value.
int solve(char* grid, int occupied_spaces) {
	for (int i = 0; i < 81; i++) {	// Examine each empty space.
		char possible_vals[9] = {'1','2','3','4','5','6','7','8','9'};
		if (grid[i] == ' ') {	// Only pay attention to the empty squares.
			// Calculate the row and column of the empty space.
			int row = i / 9;
			int column = i % 9;
		
			// Rule out numbers which already exist in the row/column.
			for (int j = 0; j < 9; j++) {
				char current_row_val = grid[row * 9 + j];
				char current_column_val = grid[column + 9 * j];
				if (current_row_val != ' ') {
					possible_vals[current_row_val - '0' - 1] = 'x';	// Remove current value from possible values list.
					//possible_vals[stoi(current_row_val) - 1] = 'x';	// Remove current value from possible values list.
				}
				if (current_column_val != ' ') {
					possible_vals[current_column_val - '0' - 1] = 'x'; // Remove current value from possible values list.
					//vals[stoi(current_column_val) - 1] = 'x'; // Remove current value from possible values list.
				}
			}
			// Rule out numbers which already exist in the current 3x3 grid.
			tuple<int, int> ninth = get_ninth(row, column); // Determine which 3x3 grid contains the empty space.
			int first_index_of_square = 3 * get<0>(ninth) + 27 * get<1>(ninth); // Find the top left index of the 3x3 grid.
			int all_indices_of_square[9] = { // Determine every index in the 3x3 grid.
				first_index_of_square, first_index_of_square + 1, first_index_of_square + 2,
				first_index_of_square + 9, first_index_of_square + 10, first_index_of_square + 11,
				first_index_of_square + 18, first_index_of_square + 19, first_index_of_square + 20
			};
			for (int j = 0; j < 9; j++) { // Examine each index in the 3x3 grid.
				char current_val = grid[all_indices_of_square[j]];
				if (current_val != ' ') {
					possible_vals[current_val - '0' - 1] = 'x'; // If a number exists in the 3x3 grid, remove it from the possible values array.
				}
			}
			
			// Iterate through the possible values list.
			int number_of_possible_values = 0;
			char new_val = 'x';
			for (int j = 0; j < 9; j++) {
				if (possible_vals[j] != 'x') { // If we find a value not equal to 'x,' hold onto it, and update the number of possible values.
					new_val = possible_vals[j];
					number_of_possible_values++;
				}
			}
			
			// If there is only one possible new value, update the grid.
			if (number_of_possible_values == 1) {
				grid[i] = new_val;
				return occupied_spaces + 1;	// This statement means exiting this function as soon as a value is added. This works well for demonstration purposes but could be changed to improve efficiency.
			}
		}
	}
	return occupied_spaces;
}

int main() {
	// gui_sudoku.py is used to convert the starting grid to a string. This file (sudoku_solver.cpp) reads this string as the starting point for solving the puzzle.
	string puzzle_data;
	getline(cin, puzzle_data);
	
	// NOTE: This grid could probably be replaced with the original string. Perhaps I could remove this in a future update?
	char* grid = new char[81];
	int occupied_spaces = 0;
	for (int i = 0; i < 81; i++) {
		grid[i] = puzzle_data[i];
		if (puzzle_data[i] != ' ') {
			occupied_spaces++;
		}
	}
	
	int steps = 0;	// Prevents infinite loop in event of error
	while (occupied_spaces < 81 && steps < 80) {	// Exit if the solution has been found or if the program cannot find a solution.
		occupied_spaces = solve(grid, occupied_spaces);
		//print_grid(grid);	// Each time a value is added, print the updated grid.
		steps++;
	}
	
	if (occupied_spaces < 81) {
		printf("Unable to find solution");
	}
	else {
		cout << grid << endl;
	}
	
	delete[] grid;
}
