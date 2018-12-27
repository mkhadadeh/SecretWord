
#ifndef POINT_H
#define POINT_H
struct Point {
	int x;
	int y;
};

typedef Point Direction;

bool operator==(Point p1, Point p2);
bool oob_pt(Point p, int max_l, int max_h);

#endif