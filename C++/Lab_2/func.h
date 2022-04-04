#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

struct TManager {
	char name[50];  // назва події
	int start_hours;    // година початку
	int start_minutes;  // хвилини початку
	int duration_hours;   // скільки триває годин
	int duration_minutes;   // скільки триває хвилин
};

struct TFreeTime {
	int start_minutes;
	int end_minutes;
	int duration;
};

void input_file(ofstream& file);
void file_output(string name);
void b_file_output(string name);
void get_time(string time, int& hours, int& minutes);
void time_out(string occasion, int hours, int minutes);
void the_nearest_case(string file_name);
string create_file(ofstream& file);
string free_time(string name_out);
void recursion(ofstream& file_in, ifstream& file_out, int upper_border, int lower_border, string name_out);

#endif