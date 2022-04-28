#include "func.h"

int main()
{
	int num;
	cout << "How many students do you want to add: ";
	cin >> num; cin.ignore(32000, '\n');
	Student* arr = createArray(num);

	int numberGroup;
	cout << "Enter the group number in which you want to know the oldest student: ";
	cin >> numberGroup; cin.ignore(32000, '\n');
	getOldestStudent(arr, numberGroup, num);

	delete[] arr;
}