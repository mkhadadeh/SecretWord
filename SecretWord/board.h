#ifndef BOARD_H

#include "piece.h"
#include "point.h"

#include <list>
#include <stack>
#include <string>

class Board
{
public:
	Board(int length, int width, std::string word_list_path);
	void output_board(std::ostream& os, char delim = ' ');
	//void output_list(std::ostream& os, char delim = '\n');

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
	//std::list<std::string> words[8];
	
	// Backtracking Info
	//std::list<std::string> used_words;


	// Grid
	char** grid;
	
	// Helper functions
	//void populate_word_list(std::string path);
	
	void populate_pieces(); // Fills up the grid with empty pieces

	//std::string random_word(int min_length = 0, int max_length = 0); // Selects a random word from the unordered_set of available words within given length parameters.
																	 //		If params out of bounds, selects any word.
	inline int random_int(int min, int max); // Selects a random integer between min and max.
	
};

#endif // !BOARD_H
