#include <algorithm>
#include "../includes/array_functions.h"
#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;
using namespace constants;

namespace KP {

	bool ascendingSort(const entry &first, const entry &second);
	bool descendingSort(const entry &first, const entry &second);
	bool occurences(const entry &first, const entry &second);

	bool ascendingSort(const entry &first, const entry &second) {
		return first.word_uppercase < second.word_uppercase;
	}

	bool descendingSort(const entry &first, const entry &second) {
		return first.word_uppercase > second.word_uppercase;
	}

	bool occurences(const entry &first, const entry &second) {
		return first.number_occurences > second.number_occurences;
	}

	void clear(std::vector<constants::entry> &entries) {
		entries.clear();
	}

	int getSize(std::vector<constants::entry> &entries) {
		return entries.size();
	}

	std::string getWordAt(std::vector<constants::entry> &entries, int i) {
		if (i > getSize(entries)) {
			return entries.at(entries.size() - 1).word;
		}
		return entries.at(i).word;
	}

	int getNumbOccurAt(std::vector<constants::entry> &entries, int i) {
		if (i > getSize(entries)){
			return entries.at(entries.size() - 1).number_occurences;
		}
		return entries.at(i).number_occurences;
	}

	bool processFile(std::vector<constants::entry> &entries,
	std::fstream &myfstream) {
		std::string s;
		while (getline(myfstream, s)) {
			if (!myfstream) {
				return false;
			}
			processLine(entries, s);
		}
		return true;
	}

	void processLine(std::vector<constants::entry> &entries, std::string &myLine) {
		std::stringstream sStr(myLine);
		std::string s;
		while (getline(sStr, s, CHAR_TO_SEARCH_FOR)) {
			processToken(entries, s);
		}
	}

	void processToken(std::vector<constants::entry> &entries, std::string &token) {
		if (strip_unwanted_chars(token) == false) {
			return;
		}
		std::string s = token;
		toUpper(s);
		int cntr = -1;
		for (unsigned int i = 0; i < entries.size(); i++) {
			if (entries[i].word_uppercase == s) {
				cntr = i;
			}
		}
		if (cntr == -1) {
			entry e {token, s, 1};
			entries.push_back(e);
		}
		else {
			entries[cntr].number_occurences++;
		}
	}

	void sort(std::vector<constants::entry> &entries, constants::sortOrder so) {
		switch (so) {
			case NONE:
				break;
			case ASCENDING:
				sort(entries.begin(), entries.end(), ascendingSort);
				break;
			case DESCENDING:
				sort(entries.begin(), entries.end(), descendingSort);
				break;
			case NUMBER_OCCURRENCES:
				sort(entries.begin(), entries.end(), occurences);
				break;
		}
	}
}
