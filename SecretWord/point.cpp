#include "point.h"

bool operator==(Point p1, Point p2) {
	return ((p1.x == p2.x) && (p1.y == p2.y));
}

bool oob_pt(Point p, int max_l, int max_h) {
	return (p.x < 0 || p.y < 0 || p.x >= max_l || p.y >= max_h);
}