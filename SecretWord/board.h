#ifndef BOARD_H

#include "piece.h"
#include "point.h"

#include <set>
#include <stack>
#include <string>

class Board
{
public:
	Board(int length, int width, std::string word_list_path);
	void output_board(std::ostream);
	void output_list(std::ostream);

private:
	// Constants
	const char NULL_C = '-';
	const int MIN_LENGTH = 3;
	const int MAX_LENGTH = 10;
	const std::set<Direction> dirs = {
		{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1},  {-1,-1}, {1,-1}, {-1,1}
	};

	// Initial Sets
	std::set<Point> available_points;
	std::set<std::string> words[8];
	
	// Backtracking Info
	struct Placed_Word { std::string word; Point start; Point end; };
	std::set<std::string> used_words;
	std::stack<Placed_Word> w_stack;

	// Grid
	char** grid;
	
	// Helper functions
	void populate_word_set(std::string path);

	void place_secret_word(); // Selects a secret word and scatters it on the grid.
	
	void populate_rest(); // Fills up the rest of the grid surrounding the secret word.
	void return_top_from_stack(); // Pops stack and returns possible points and the word to the set of words.
	void place_word(std::string word); // Places a word on the grid, removing availability of its points, and pushing it onto the stack.
	char get_adjacent(Point current, Direction dir); // Gets the adjacent character, throwing an exception if out of bounds.

	std::string random_word(int min_length = 0, int max_length = 0); // Selects a random word from the set of available words within given length parameters.
																	 //		If params out of bounds, selects any word.
	Point random_point(); // Selects a random point from the available points.
	Direction random_direction(const std::set<Direction>& possible_dirs); // Selects a direction from the given directions.
	int random_int(int min, int max); // Selects a random integer between min and max.
	
};

#endif // !BOARD_H
