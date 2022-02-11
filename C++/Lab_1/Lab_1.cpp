#include "lib.h"

int main() {
	const char* initFile = "initFile.txt"; // початковий файл
	const char* editFile = "editFile.txt";   // змінений файл
	inputFile(initFile);
	rewriteFile(initFile, editFile);
	cout << "initFile.txt:\n";
	outFile(initFile);
	cout << "editFile.txt:\n";
	outFile(editFile);
	return 0;
}