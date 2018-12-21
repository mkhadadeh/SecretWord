#ifdef WORD_TRIMMER

#include <fstream>
#include <set>
#include <string>

using namespace std;

bool repeats(string s);

int main() {
	string next;
	set<string> b;

	ifstream bifs;
	bifs.open("blacklist.txt");
	if (bifs.fail()) {
		return 1;
	}

	while (getline(bifs, next))
		b.insert(next);

	bifs.close();
	next = "";

	ifstream ifs;
	ifs.open("words.txt");
	if (ifs.fail()) {
		return 1;
	}
	
	ofstream ofs;
	ofs.open("words_trimmed.txt");
	if (ofs.fail()) {
		return 1;
	}

	while (getline(ifs, next)) {
		bool add = true;
		if (next.length() < 3 || next.length() > 10)
			continue;
		if (repeats(next))
			continue;
		if (b.find(next) != b.end())
			continue;
		for (char& c : next) {
			if (!(c >= 'a' && c <= 'z'))
				add = false;
		}
		if (add) {
			ofs << next << '\n';
		}
	}

	ifs.close();
	ofs.close();


	return 0;
}

bool repeats(string s) {
	char check = s[0];
	int times = 1;

	for (int i = 1; i < s.length(); i++) {
		if (s[i] == check) {
			times++;
			if (times > 1)
				return true;
		}
		else {
			check = s[i];
			times = 1;
		}
	}
	return false;
}

#endif