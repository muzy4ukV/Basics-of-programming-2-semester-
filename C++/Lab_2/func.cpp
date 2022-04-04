#include "func.h"

string create_file(ofstream& file) {
	string file_name;
	cout << "Enter a file name: ";
	getline(cin, file_name);
	cout << "How do you want to add text\n1) append to existing file \n2) create " <<
		"new file\n(Write 1 or 2)" << endl;
	while (true)
	{
		int howOpen; cin >> howOpen;
		if (howOpen == 1)
		{
			file.open("Files/" + file_name, ios::binary | ios::app);
			break;
		}
		else {
			if (howOpen == 2) {
				file.open("Files/" + file_name, ios::binary);
				break;
			}
			else {
				cout << "Incorrect input. Try again" << endl;
			}
		}
	}
	if (!file.is_open())
	{
		cerr << "Couldn't open the file";
		exit(0);
	}
	return "Files/" + file_name;
}

void input_file(ofstream& file) {
	TManager my_case;
	int num;
	cout << "How many cases do you have today: ";
	cin >> num; cin.ignore(32767, '\n');
	if (num <= 0) {
		cout << "Today you have a chill day. Have a rest :)";
		exit(0);
	}
	for (int i = 0; i < num; i++)
	{
		string time;
		cout << "Name: "; cin.getline(my_case.name, 50);
		cout << "Start hour (HH:MM): "; getline(cin, time);
		get_time(time, my_case.start_hours, my_case.start_minutes);
		cout << "Duration (HH:MM): "; getline(cin, time);
		get_time(time, my_case.duration_hours, my_case.duration_minutes);
		file.write((char*)&my_case, sizeof(TManager));
	}
	file.close();
}

void get_time(string time, int& hours, int& minutes) {
	if (time.empty())
	{
		cerr << "Incorrectly entered data";
		exit(0);
	}
	int find_symb;
	find_symb = time.find(":");
	if (find_symb == -1)
	{
		cerr << "Incorrectly entered data";
		exit(0);
	}
	hours = stoi(time.substr(0, find_symb));
	minutes = stoi(time.substr(find_symb + 1, 2));
	if (minutes >= 60 || hours >= 24 || minutes < 0 || hours < 0)
	{
		cerr << "Incorrectly entered time";
		exit(0);
	}
}

void file_output(string name) {
	ifstream file(name, ios::binary);
	TManager my_case;
	cout << "\n===========////===========\n\n" << name << '\n';
	while (file.read((char*)&my_case, sizeof(TManager)))
	{
		cout << "\nName of occasion: " << my_case.name << endl;

		time_out("Starts at", my_case.start_hours, my_case.start_minutes);
		time_out("Duration", my_case.duration_hours, my_case.duration_minutes);

		int end_hours = my_case.start_hours + my_case.duration_hours;
		int end_minutes = my_case.start_minutes + my_case.duration_minutes;

		if (end_minutes >= 60) {
			end_minutes -= 60;
			end_hours++;
		}
		if (end_hours >= 24) {
			end_hours %= 24;
		}
		time_out("End time", end_hours, end_minutes);
	}
	cout << "\n===========////===========\n\n";
	file.close();
}

void time_out(string occasion, int hours, int minutes) {
	cout << occasion << ((hours < 10) ? ": 0" : ": ") << hours;
	cout << ((minutes < 10) ? ":0" : ":") << minutes << endl;
}

void the_nearest_case(string file_name) {

	struct tm current_time;
	time_t t = time(0);
	localtime_s(&current_time, &t);

	ifstream file(file_name, ios::binary);
	TManager my_case;

	char nearest_case[50];
	int current_minutes = current_time.tm_hour * 60 + current_time.tm_min;
	int nearest_minutes = 1440; // максимальна кількість хвилин в добі

	while (file.read((char*)&my_case, sizeof(TManager)))
	{
		int temp_minutes = my_case.start_hours * 60 + my_case.start_minutes;
		if (current_minutes <= temp_minutes && nearest_minutes >= temp_minutes) {
			nearest_minutes = temp_minutes;
			strcpy_s(nearest_case, my_case.name);
		}
	}

	if (nearest_minutes != 1440) {
		cout << "Your next occasion is - " << nearest_case;
		time_out(" and it starts at", nearest_minutes / 60, nearest_minutes % 60);
	}
	else
		cout << "All your occasions is over. Have a rest!\n" << endl;
	file.close();
}

string free_time(string name_out) {
	ofstream file_in;
	string name_in = create_file(file_in);
	ifstream file_out(name_out, ios::binary);
	recursion(file_in, file_out, 780, 1440, name_out);
	file_in.close();
	return name_in;
}


void recursion(ofstream& file_in, ifstream& file_out, int upper_border, int lower_border, string name_out) {
	TManager case_out;
	if (!file_out.read((char*)&case_out, sizeof(TManager)))
	{
		file_out.close();
		TFreeTime t;
		t.start_minutes = upper_border;
		t.end_minutes = lower_border;
		t.duration = lower_border - upper_border;
		file_in.write((char*)&t, sizeof(TFreeTime));
		return;
	}
	else {
		int start_time = case_out.start_hours * 60 + case_out.start_minutes;
		int end_time = start_time + case_out.duration_hours * 60 + case_out.duration_minutes;
		if (start_time <= upper_border && end_time < lower_border && end_time > upper_border)
		{
			upper_border = end_time;
			recursion(file_in, file_out, upper_border, lower_border, name_out);
		}
		else if (start_time > upper_border && end_time >= lower_border && start_time < lower_border)
		{
			lower_border = start_time;
			recursion(file_in, file_out, upper_border, lower_border, name_out);
		}
		else if (start_time > upper_border && end_time < lower_border)
		{
			int position = file_out.tellg();
			recursion(file_in, file_out, upper_border, start_time, name_out);
			ifstream file_out2(name_out, ios::binary);
			file_out2.seekg(position, ios::beg);
			recursion(file_in, file_out2, end_time, lower_border, name_out);
		}
		else if ((start_time < upper_border && end_time <= upper_border) || (start_time >= lower_border && end_time > lower_border))
		{
			recursion(file_in, file_out, upper_border, lower_border, name_out);
		}
		else if (start_time <= upper_border && end_time >= lower_border)
			return;
		else {
			cout << "Something went wrong :(\nCheck your input data" << endl;
			exit(0);
		}
	}
}

void b_file_output(string name) {
	ifstream file(name, ios::binary);
	TFreeTime time;
	cout << "\n===========////===========\n\n" << name << '\n';
	while (file.read((char*)&time, sizeof(TFreeTime)))
	{
		time_out("\nFree time starts at", time.start_minutes / 60, time.start_minutes % 60);
		time_out("Ends at", time.end_minutes / 60, time.end_minutes % 60);
		time_out("Duration", time.duration / 60, time.duration % 60);
	}
	cout << "\n===========////===========\n\n";
	file.close();
}
