#include "board.h"
#include <cstdlib>
#include <ctime>

// NOTE grid indexing is done the following way grid[row][column]
// Point and Direction structs have x and y values
// x corresponds to column
// y corresponds to row

Board::Board(int length, int width, std::string word_list_path)
{
	// Initialize values and rand()
	col_count = length;
	row_count = width;
	srand(time(NULL));

	//populate_word_set(word_list_path);
	
	// Create grid
	grid = new char*[row_count];
	for (int i = 0; i < row_count; i++) {
		grid[i] = new char[col_count];
	}

	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			grid[i][j] = NULL_C;
			available_points.push_back({j,i});
		}
	}

	// Create list of pieces
	for (const Direction& dir : dirs) {
		for (int i = MIN_LENGTH; i <= MAX_LENGTH; i++) {
			all_pieces.push_back(Piece(i, dir));
		}
	}

	// Fill up the grid with pieces
	populate_pieces();
}

void Board::output_board(std::ostream& os) {
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			os << grid[i][j] << ' ';
		}
		os << '\n';
	}
}

void Board::populate_pieces() {
	char counter = 'A';
	while (!available_points.empty()) {
		auto it = available_points.begin();
		grid[it->y][it->x] = counter++;
		available_points.erase(it);
	}
}

int Board::random_int(int min, int max) {
	return (min + rand() % (max - min + 1));
}