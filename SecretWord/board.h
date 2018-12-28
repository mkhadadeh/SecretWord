#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "point.h"
#include "word_entry.h"

#include <list>
#include <stack>
#include <string>
#include <set>

class Board
{
public:
	Board(int length, int width, std::string no_def_word_list_path, std::string def_words);
	void output_board(std::ostream& os, char delim = ' ');
	void output_list(std::ostream& os, char delim = '\n');
	void output_hint(std::ostream& os, char delim = '\n');

private:
	int row_count;
	int col_count;
	// Constants
	const char NULL_C = '-';
	const int MIN_LENGTH = 3;
	const int MAX_LENGTH = 9;
	const std::list<Direction> dirs = {
		{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1},  {-1,-1}, {1,-1}, {-1,1}
	};

	// Initial unordered_sets
	std::list<Point> all_points;
	std::list<Piece> all_pieces;
	std::set<std::string> words[7];
	std::set<Word_Entry> secret_word_lists[7];
	
	// Word Info
	std::set<std::string> used_words;
	Word_Entry secret_word;

	// Grid
	char** grid;
	
	std::stack<Piece> p_stack;
	int secret_word_length;

	// Helper functions
	void populate_word_lists(std::string no_def_path, std::string def_path);
	
	void populate_pieces(); // Fills up the grid with empty pieces

	std::string random_word(int length); // Selects a random word from the unordered_set of available words within given length parameters.
																	 //		If params out of bounds, selects any word.
	Word_Entry random_secret_word(int length); // Selects a random secret word
	inline int random_int(int min, int max); // Selects a random integer between min and max.

	char remove_random_character(std::string& s);
	
};

#endif
