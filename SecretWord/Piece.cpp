#include "piece.h"
#include <algorithm>


Piece::Piece(int length, Direction dir) {
	init_dir = dir;
	full_dir.x = dir.x * length;
	full_dir.y = dir.y * length;
	start = { -1,-1 };
	len = length;
}

bool Piece::can_place(Point p, std::list<Point>& available) {
	place(p);
	for (Point pt : pts_covered()) {
		if (std::find(available.begin(), available.end(), pt) == available.end()) {
			remove();
			return false;
		}
	}
	remove();
	return true;
}

void Piece::place(Point p) {
	start = p;
}

std::list<Point> Piece::pts_covered() {
	// Returns all points covered by the piece
	std::list<Point> pts;
	Point next;
	Direction next_dir;
	for (int i = 0; i < len; i++) {
		next_dir = { init_dir.x * i, init_dir.y * i };
		next = { start.x + next_dir.x, start.y + next_dir.y };
		pts.push_back(next);
	}
	return pts;
}

void Piece::remove() {
	start = { -1,-1 };
}

void Piece::place_word(std::string word, char** grid) {
	// Places a word in the piece on the grid
	int counter = 0;
	for (const Point& p : pts_covered()) {
		grid[p.y][p.x] = word[counter++];
	}
	this_word = word;
}

void Piece::placeholder(char c, char** grid) {
	// ONLY FOR DEBUGGING. Places a single character throughout a full piece
	// to distinguish it from others.
	for (const Point& p : pts_covered()) {
		grid[p.y][p.x] = c;
	}
}

std::string Piece::debug_str() {
	std::string str = "";
	str += "Start: ";
	str += std::to_string(start.x);
	str += ' ';
	str += std::to_string(start.y);
	str += "   Length: ";
	str += std::to_string(get_length());
	str += "   Direction: ";
	str += std::to_string(init_dir.x);
	str += ' ';
	str += std::to_string(init_dir.y);
	return str;
}

bool Piece::operator==(Piece p) {
	return ((len == p.len) && (init_dir == p.init_dir));
}