from lib import *

name_out = "Files/" + input("Enter a file name: ")

output_file = create_file(name_out)
input_file(output_file)
file_output(name_out)
the_nearest_case(name_out)

name_in = "Files/" + input("Enter a file name: ")
free_time(name_out, name_in)
b_file_output(name_in)