#define WORD_LIST_GEN_MAIN
#ifndef WORD_LIST_GEN_MAIN

// TODO: Extract all nouns, verbs, adjectives (from 3 to 9 letters) from oxford dictionary
// TODO: Cross reference words from most freq. words list with oxford nouns and place into a set of common words
// TODO: Place all the rest of the nouns + definitions in a set of uncommon words to be used as secret words

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

#include "word_entry.h"

using namespace std;

int main() {
	set<string> common10000;
	set<string> blacklist;

	set<Word_Entry> common;
	set<Word_Entry> uncommon;

	// Extract common and blacklisted words
	ifstream c_ifs;
	c_ifs.open("freq_list.txt");
	if (c_ifs.fail()) {
		cout << "Couldn't open freq_list" << endl;
		return 1;
	}
	string next_c;
	while (getline(c_ifs, next_c)) {
		common10000.insert(next_c);
	}
	c_ifs.close();


	ifstream b_ifs;
	b_ifs.open("blacklist.txt");
	if (b_ifs.fail()) {
		cout << "Couldn't open blacklist" << endl;
		return 1;
	}
	string next_b;
	while (getline(b_ifs, next_b)) {
		blacklist.insert(next_b);
	}
	b_ifs.close();

	// Extract from oxford
	ifstream ifs;
	ifs.open("oxford.txt");
	if (ifs.fail()) {
		cout << "Couldn't open oxford dictionary" << endl;
		return 1;
	}
	
	string next_word;
	string pos;
	string next_def;

	while (!ifs.eof()) {
		bool add = true;
		ifs >> next_word;
		std::transform(next_word.begin(), next_word.end(), next_word.begin(), ::tolower);
		ifs >> pos;
		getline(ifs, next_def);
		if (!(pos == "n." || pos == "v." || pos == "adj.")) {
			continue;
		}
		if (blacklist.count(next_word) != 0) {
			continue;
		}
		if (next_word.length() > 9 || next_word.length() < 3) {
			continue;
		}
		for (char& c : next_word) {
			if (!(c >= 'a' && c <= 'z'))
				add = false;
		}
		if (add) {
			Word_Entry w;
			w.word = next_word;
			w.def = pos + " " + next_def;
			if (common10000.count(next_word) > 0) {
				common.insert(w);
			}
			else {
				uncommon.insert(w);
			}
		}
	}
	ifs.close();

	// Export common words

	ofstream ofs_w;
	ofstream ofs_wo;

	ofs_w.open("common_def.txt");
	ofs_wo.open("common_nodef.txt");

	for (const Word_Entry & w : common) {
		ofs_w << w.word << " " << w.def << endl;
		ofs_wo << w.word << endl;
	}

	ofs_w.close();
	ofs_wo.close();

	// Export uncommon words

	ofs_w.open("uncommon_def.txt");
	ofs_wo.open("uncommon_nodef.txt");

	for (const Word_Entry & w : uncommon) {
		ofs_w << w.word << " " << w.def << endl;
		ofs_wo << w.word << endl;
	}

	ofs_w.close();
	ofs_wo.close();

	return 0;
}

#endif