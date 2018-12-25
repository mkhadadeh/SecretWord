#include <iostream>
#include "board.h"

using namespace std;

int main() {
	Board b(10, 15, "");
	b.output_board(cout);
	return 0;
}