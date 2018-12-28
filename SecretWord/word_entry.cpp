#include "word_entry.h"

bool operator<(Word_Entry w1, Word_Entry w2) {
	return (w1.word < w2.word);
}

bool operator==(Word_Entry w1, Word_Entry w2) {
	return (w1.word == w2.word);
}