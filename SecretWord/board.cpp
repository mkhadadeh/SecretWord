#include "board.h"
#include "point.h"
#include <cstdlib>
#include <ctime>
#include <iostream> // FOR DEBUGGING

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
			all_points.push_back({j,i});
		}
	}

	// Create list of pieces
	for (const Direction& dir : dirs) {
		for (int i = MIN_LENGTH; i <= MAX_LENGTH; i++) {
			all_pieces.push_back(Piece(i, dir));
		}
	}
	Piece s_word_piece(1, { 1,1 });
	all_pieces.push_back(s_word_piece);

	// Fill up the grid with pieces
	populate_pieces();
}

void Board::output_board(std::ostream& os, char delim) {
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			os << grid[i][j] << delim;
		}
		os << '\n';
	}
}

void Board::populate_pieces() {
	char rep = 'A'; // FOR DEBUGGING
	int secret_word_length = 0;
	std::list<Piece> possible_pieces;
	bool just_backtracked = false;
	int tolerance = 0;
	bool reached_tolerance = false;
	auto available_points = all_points;
	std::stack<Piece> p_stack;
	std::stack<std::list<Piece>> backtracking_lists;

	while (!available_points.empty()) {
		Point this_pt = *(available_points.begin());
		if (oob_pt(this_pt, col_count, row_count)) {
			available_points.remove(this_pt);
			continue;
		}
		// Place possible pieces in a list
		if (possible_pieces.empty() && !just_backtracked) {
			for (Piece p : all_pieces) {
				if (p.can_place(this_pt, available_points)) {
					possible_pieces.push_back(p);
				}
			}
		}

		// If piece can be placed
		if (!possible_pieces.empty() && secret_word_length < MAX_LENGTH) {
			// Place and add to stack
			std::list<Piece>::iterator it;
			it = std::next(possible_pieces.begin(), random_int(0, possible_pieces.size() - 1));
			Piece to_place = *it;
			if (to_place.get_length() == 1) {
				secret_word_length++;
			}
			to_place.place(this_pt);

			p_stack.push(to_place);
			//std::cout << "Pushed: " << to_place.debug_str() << std::endl;
			backtracking_lists.push(possible_pieces);
			// Remove covered pts
			for (Point pt : to_place.pts_covered()) {
				available_points.remove(pt);
			}
			possible_pieces.clear();
			just_backtracked = false;
		}
		else {
				// Backtrack and remove previous piece from stack
				auto prev_piece = p_stack.top();
				p_stack.pop();
				auto prev_list = backtracking_lists.top();
				prev_list.remove(prev_piece);
				backtracking_lists.pop();

				for (Point pt : prev_piece.pts_covered()) {
					available_points.push_back(pt);
				}
				possible_pieces.clear();
				for (Piece p : prev_list) {
					if (p.can_place(this_pt, available_points)) {
						possible_pieces.push_back(p);
					}
				}
				if (prev_piece.get_length() == 1) {
					secret_word_length--;
				}
				//std::cout << "Popped: " << prev_piece.debug_str() << std::endl;
				just_backtracked = true;
		}
		/*if (tolerance++ >= 10000) {
			reached_tolerance = true;
			break;
		}*/
	}
	if (!reached_tolerance) {
		while (!p_stack.empty()) {
			if (p_stack.top().get_length() == 1) {
				p_stack.top().placeholder('$', grid);
			}
			else {
				p_stack.top().placeholder(rep++, grid);
			}
			p_stack.pop();
		}
	}
	else {
		std::cout << "Reached tolerance. Repopulating..." << std::endl;
		populate_pieces();
	}
}

int Board::random_int(int min, int max) {
	return (min + rand() % (max - min + 1));
}