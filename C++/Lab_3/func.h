#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
	string fullName;
	int numGroup;
	int birthDay;
	int birthMonth;
	int birthYear;
public:
	Student();
	Student(string name, int group, string date);
	int getAge();
	int getGroup();
	void getInfo();
};

Student* createArray(int num);
void getDate(string line, int& day, int& month, int& year);
void getOldestStudent(Student* arr, int numberGroup, int amount);

#endif
