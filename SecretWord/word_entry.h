#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <string>

struct Word_Entry {
	std::string word;
	std::string def; // Includes POS
};


bool operator<(Word_Entry w1, Word_Entry w2);
bool operator==(Word_Entry w1, Word_Entry w2);

#endif // !WORD_ENTRY_H