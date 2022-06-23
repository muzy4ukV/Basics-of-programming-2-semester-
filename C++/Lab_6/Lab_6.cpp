#include "tree.h"

int main() {
	int value, how_print; bool flag = true;
	while (flag) {
		try {
			cout << "Enter a number: ";
			string input;
			cin >> input;
			value = stoi(input);
			if (value <= 0) throw "You enter wrong number of nodes";

			cout << "How you want to print tree: 0 - vertically, 1 - horizontally?" << endl;
			cin >> input;
			how_print = stoi(input);

			if (how_print != 0 && how_print != 1) throw "You have entered wrong number for print method";
			flag = false;

		}
		catch (const invalid_argument& ex) {
			cout << "The entered numbers is incorrect\nTry again" << endl;
		}
		catch (const char* arr) {
			cout << arr << endl << "Try again" << endl;
		}
	}

	BinaryTree tree;
	tree.createTree(value);
	
	if (how_print == 0)
		tree.printVertical();
	else
		tree.printHorizontal();

	return 0;
}
