#include <iostream>
using namespace std;

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

int solve(char* grid, int occupied_spaces) {
	char possible_vals[9] = {'1','2','3','4','5','6','7','8','9'};
	for (int i = 0; i < 81; i++) {
		if (grid[i] == ' ') {	// Only pay attention to the empty squares.
			int row = i / 9;
			int column = i % 9;
			printf("Empty space at (%d,%d)\n", column, row);
		}
	}
	return occupied_spaces;
}

int main() {
	char* grid = initialize_grid();
	print_grid(grid);
	int occupied_spaces = 58;
	int steps = 0;	// Temp measure to prevent infinite loop
	occupied_spaces = solve(grid, steps);
	while (contains_blanks && steps < 80) {
		print_grid(grid);
		steps++;
	}
	delete[] grid;
}
