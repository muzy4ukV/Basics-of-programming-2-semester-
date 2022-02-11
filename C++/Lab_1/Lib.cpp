#include "lib.h"

void inputFile(const char* name) {
	cout << "How you want to add text\n1) append to existing file \n2) create " << 
	"new\n(Write First or Second)" << endl;
	ofstream file;
	while (true)
	{
		string howOpen;
		getline(cin, howOpen);
		if (!howOpen.compare("First")) {
			file.open(name, ios::app);
			break;
		}
		else {
			if (!howOpen.compare("Second")) {
				file.open(name);
				break;
			}
			else {
				cout << "Incorrect input. Try again" << endl;
			}
		}
	}
	if (file) {
		string newLine;
		cout << "Input your text\nPress ENTER to begin new line and press CTRL+Z to finish" << endl;
		while (getline(cin, newLine, char(26))) {
			file << newLine;
		}
		cout << endl;
		file.close();
	} else {
		cerr << "initFile.txt couldn't be opened";
		exit(1);
	}
}


void rewriteFile(const char* name1, const char* name2) {
	ifstream outFile(name1);
	ofstream inputFile(name2);

	string line;
	while (!outFile.eof()) {
		getline(outFile, line);
		if (!line.empty())
		{
			int lastSpace = findLastWord(line);
			inputFile << line[lastSpace + 1] << " - " << line << '\n';
		}
	}
	outFile.close();
	inputFile.close();
}

int findLastWord(string str) {
	while (true)
	{
		if (str.empty()) return 0;
		char lastSymbol = str[str.length() - 1];
		if (lastSymbol == ' ')
		{
			str.pop_back();
		}
		else break;
	}
	int lastSpace = str.rfind(' ');
	return lastSpace;
}


void outFile(const char* name) {
	ifstream file(name);
	string str;
	while (!file.eof()) {
		getline(file, str);
		cout << str << endl;
	}
	cout << "\n";
	file.close();
}