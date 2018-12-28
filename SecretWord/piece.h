#ifndef PIECE_H
#define PIECE_H

#include "point.h"
#include <list>
#include <string>

class Piece
{
public:

	Piece(int length, Direction dir);

	bool can_place(Point p, std::list<Point>& available);
	
	void place(Point p);
	void remove();

	void place_word(std::string word, char** grid);
	void placeholder(char c, char** grid); // ONLY FOR DEBUGGING

	std::list<Point> pts_covered();
	int get_length() { return len; }
	Point get_start() { return start; }

	std::string debug_str();

	bool operator==(Piece p);

private:
	int len;
	Direction init_dir; // "unit" direction
	Direction full_dir; // direction and length
	Point start;
	std::string this_word;
};
#endif