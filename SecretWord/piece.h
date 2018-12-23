#pragma once

#include "point.h"
#include <set>

class Piece
{
public:
	Piece(int length, Direction dir);
	bool can_place(Point p, char** grid, int grid_length, int grid_height);
	void place(Point p);
	std::set<Point> pts_covered();
	void remove();
private:
	int len;
	Direction init_dir;
	Direction full_dir;
	Point start;
};

