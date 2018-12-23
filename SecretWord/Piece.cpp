#include "piece.h"



Piece::Piece(int length, Direction dir) {
	init_dir = dir;
	full_dir.x = dir.x * length;
	full_dir.y = dir.y * length;
	start = { -1,-1 };
	len = length;
}

bool Piece::can_place(Point p, char** grid, int grid_length, int grid_height) {
	// Bounds check
	Point final_pt = { p.x + full_dir.x, p.y + full_dir.y };
	if (final_pt.x >= grid_length || final_pt.y >= grid_height || final_pt.x < 0 || final_pt.y < 0)
		return false;
	
	// Availability check
	Point next;
	Direction next_dir;
	for (int i = 0; i < len; i++) {
		next_dir = { init_dir.x * i, init_dir.y * i };
		next = { p.x + next_dir.x, p.y + next_dir.y };
		if (grid[next.x][next.y] != '-') {
			return false;
		}
	}

	return true;
}

void Piece::place(Point p) {
	start = p;
}

std::set<Point> Piece::pts_covered() {
	std::set<Point> pts;
	Point next;
	Direction next_dir;
	for (int i = 0; i < len; i++) {
		next_dir = { init_dir.x * i, init_dir.y * i };
		next = { start.x + next_dir.x, start.y + next_dir.y };
		pts.insert(next);
	}
	return pts;
}

void Piece::remove() {
	start = { -1,-1 };
}