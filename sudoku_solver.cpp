#include <iostream>
#include <string>
#include <tuple>
using namespace std;

// Note: The initialized grid is bad.

char* initialize_grid() {
	char* grid = new char[81];
	
	// Define the Sudoku grid as a one-dimensional character array
    	char temp[81] = {
		'6', '8', ' ', '4', ' ', '3', ' ', '5', ' ',
		'4', ' ', '2', ' ', '5', '3', '6', '8', ' ',
		'5', '9', '3', '6', '7', '8', ' ', '4', ' ',
		' ', '1', '7', '2', '8', '6', '9', '4', '5',
		'8', '9', '5', ' ', '4', '2', ' ', '7', ' ',
		'2', '5', '4', '3', '9', '7', '8', '1', ' ',
		'7', ' ', '8', '3', '1', '5', '9', '2', ' ',
		'9', '3', '5', ' ', '6', ' ', '4', '1', ' ',
		'2', ' ', '9', ' ', '5', ' ', '7', '3', ' '
   	 };
   	 
   	for (int i = 0; i < 81; i++) { // Dynamically allocate array
   		grid[i] = temp[i];
   	}
	
	return grid;
}

void print_grid(char* grid) {
	for (int i = 0; i < 9; i++) {	// For every column
		printf("-------------------");
		printf("\n");
		for (int j = 0; j < 9; j++) {	// Print row
			printf("|%c", grid[9 * i + j]);
		}
		printf("|");
		printf("\n");
	}
	printf("-------------------\n");
}

bool contains_blanks(char* grid) {
	for (int i = 0; i < 81; i++) {
		if (grid[i] == 0) {
			return true;
		}
	}
	return false;
}

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

int solve(char* grid, int occupied_spaces) {
	char possible_vals[9] = {'1','2','3','4','5','6','7','8','9'};
	for (int i = 0; i < 81; i++) {
		if (grid[i] == ' ') {	// Only pay attention to the empty squares.
			// Calculate the row and column of the empty space.
			int row = i / 9;
			int column = i % 9;
			
			//printf("Empty space at (%d,%d)\n", column, row);	// TEMP
			
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
					possible_vals[current_val - '0' - 1] = 'x'; // As needed, remove values from the possible_vals array.
					//possible_vals[stoi(current_val) - 1] = 'x'; // As needed, remove values from the possible_vals array.
				}
			}
			
			// Iterate through the possible values list.
			int number_of_possible_values = 0;
			char new_val = 'x';
			for (int j = 0; j < 9; j++) {
				if (possible_vals[j] != 'x') { // If we find a value not equal to 'x' hold onto it, and update the number of possible values.
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
	char* grid = initialize_grid();
	print_grid(grid);
	int occupied_spaces = 58;
	int steps = 0;	// Temp measure to prevent infinite loop
	while (occupied_spaces < 81 && steps < 80) {
		solve(grid, occupied_spaces);
		print_grid(grid);
		steps++;
	}
	delete[] grid;
}
