#define GRID_GEN_MAIN
#ifndef GRID_GEN_MAIN

#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main() {
	Board b(10, 10, "");
	ofstream ofs;
	ofs.open("test.txt");
	if (!ofs.fail()) {
		b.output_board(ofs,',');
		ofs.close();
	}
	return 0;
}
#endif // !GRID_GEN_MAIN