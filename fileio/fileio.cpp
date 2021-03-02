#include "../includes/fileio.h"
#include "../includes/constants.h"
using namespace std;
using namespace constants;

bool emptyFile(fstream &myfile);

bool emptyFile(fstream &myfile) {
	return myfile.peek() == fstream::traits_type::eof();
}

bool openFile(fstream &myfile, const string &myFileName,
ios_base::openmode mode) {
	myfile.open(myFileName.c_str(), mode);
	if (!emptyFile(myfile)) {
		if (myfile.is_open()) {
			return true;
		}
	}
	return false;
}

void closeFile(fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

int writetoFile(vector<entry> &entries, const string &outputfilename) {
	ofstream output;
	output.open(outputfilename.c_str());
	if (!output.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}
	else if (entries.empty()) {
		return FAIL_NO_ARRAY_DATA;
	}
	for (unsigned int i = 0; i < entries.size(); i++) {
		output << entries[i].word << " " << entries[i].number_occurences << endl;
	}
	return SUCCESS;
}
