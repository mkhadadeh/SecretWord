#ifndef GRID_GEN_MAIN

#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main() {
	Board b(9, 9, "common_nodef.txt", "common_def.txt");
	ofstream ofs;
	ofs.open("test.txt");
	if (!ofs.fail()) {
		b.output_board(ofs,',');
		ofs << "\nWords:\n";
		b.output_list(ofs);
		ofs << "\nSecret Word Hint:\n";
		b.output_hint(ofs);
		ofs.close();
	}
	return 0;
}
#endif // !GRID_GEN_MAIN