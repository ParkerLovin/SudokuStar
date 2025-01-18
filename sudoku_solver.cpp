#include <iostream>
using namespace std;

char* initialize_grid() {
	char* grid = new char[81];
	for (int i = 0; i < 81; i++) {
		grid[i] = '0';
	}
	return grid;
}

void print_grid(char* grid) {
	for (int i = 0; i < 9; i++) {
		printf("-------------------");
		printf("\n");
		for (int j = 0; j < 9; j++) {	// print row
			printf("|%c", grid[9 * i + j]);
		}
		printf("|");
		printf("\n");
	}
	printf("-------------------\n");
}

int main() {
	char* grid = initialize_grid();
	print_grid(grid);
}
