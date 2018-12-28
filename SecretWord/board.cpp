#include "board.h"
#include "point.h"
#include <cstdlib>
#include <ctime>
#include <iostream> // FOR DEBUGGING
#include <fstream>

// NOTE grid indexing is done the following way grid[row][column]
// Point and Direction structs have x and y values
// x corresponds to column
// y corresponds to row

Board::Board(int length, int width, std::string no_def_word_list_path, std::string def_words)
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

	// Fill up the grid with pieces containing the words
	do {
		while (!p_stack.empty()) {
			p_stack.pop();
		}
		populate_pieces();
	} while (secret_word_length < 3);
	populate_word_lists(no_def_word_list_path, def_words);
	secret_word = random_secret_word(secret_word_length);
	std::string secret_word_copy = secret_word.word;
	while (!p_stack.empty()) {
		Piece next_piece = p_stack.top();
		p_stack.pop();
		if (next_piece.get_length() == 1) {
			// If secret word tile
			if (secret_word_copy.length() == 1) {
				next_piece.placeholder(secret_word_copy[0], grid);
			}
			else {
				next_piece.placeholder(remove_random_character(secret_word_copy), grid);
			}
		}
		else {
			std::string next_word;
			do {
				next_word = random_word(next_piece.get_length());
			} while (used_words.count(next_word) > 0 || next_word == secret_word.word);
			next_piece.place_word(next_word, grid);
			used_words.insert(next_word);
		}
	}
}

void Board::output_board(std::ostream& os, char delim) {
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			os << grid[i][j] << delim;
		}
		os << '\n';
	}
}

void Board::output_list(std::ostream& os, char delim) {
	for (std::string w : used_words) {
		os << w << delim;
	}
}

void Board::output_hint(std::ostream& os, char delim) {
	os << secret_word.def << delim;
}

void Board::populate_pieces() {
	char rep = 'A'; // FOR DEBUGGING
	secret_word_length = 0;
	std::list<Piece> possible_pieces;
	bool just_backtracked = false;
	auto available_points = all_points;
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
	}
}

int Board::random_int(int min, int max) {
	return (min + rand() % (max - min + 1));
}

void Board::populate_word_lists(std::string no_def_path, std::string def_path) {
	std::ifstream ifs;
	ifs.open(no_def_path);
	if (ifs.fail()) {
		std::cout << "Could not open " << no_def_path << std::endl;
		exit(1);
	}
	std::string next;
	while (getline(ifs, next)) {
		words[next.length() - 3].insert(next);
	}
	ifs.close();

	ifs.open(def_path);
	if (ifs.fail()) {
		std::cout << "Could not open " << def_path << std::endl;
		exit(1);
	}
	std::string next_word;
	std::string next_def;
	while (!ifs.eof()) {
		ifs >> next_word;
		getline(ifs, next_def);
		Word_Entry w = { next_word,next_def };
		secret_word_lists[next_word.length() - 3].insert(w);
	}
	ifs.close();
}

std::string Board::random_word(int length) {
	int size_of_set = words[length - 3].size();
	auto it = words[length - 3].begin();
	std::advance(it, random_int(0, size_of_set - 1));
	return *it;
}

Word_Entry Board::random_secret_word(int length) {
	int size_of_set = secret_word_lists[length - 3].size();
	auto it = secret_word_lists[length - 3].begin();
	std::advance(it, random_int(0, size_of_set - 1));
	return *it;
}

char Board::remove_random_character(std::string& s) {
	int idx = random_int(0, s.length() - 1);
	char chosen = s[idx];
	s.erase(s.begin() + idx);
	return chosen;
}