#include "func.h"

int main()
{
	ofstream file_out;
	string name_out = create_file(file_out);
	input_file(file_out);
	file_output(name_out);
	the_nearest_case(name_out);
	file_out.close();

	string name_in = free_time(name_out);
	b_file_output(name_in);

	return 0;
}