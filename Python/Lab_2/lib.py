import pickle
from datetime import datetime


def create_file(file_name):
    print("How do you want to add information\n1) append to existing file \n2) create new file")
    while (True):
        how_open = int(input("Choose 1 or 2: "))
        if how_open == 1:
            file = open(file_name, "ab")
            break
        elif how_open == 2:
            file = open(file_name, "wb")
            break
        else:
            print("Incorrect input. Try again")
    return file

def get_time(string):
    if (not string):
        print("Incorrectly entered data")
        exit(0)
    find_symb = string.find(":")
    if find_symb == -1:
        print("Incorrectly entered data")
        exit(0)
    hours = int(string[0:find_symb])
    minutes = int(string[find_symb + 1:])
    if (minutes >= 60 or hours >= 24 or minutes < 0 or hours < 0):
        print("Incorrectly entered data")
        exit(0)
    return (hours * 60 + minutes)


def input_file(file):
    times = int(input("How many cases do you have today: "))
    if times < 0: 
        print("Today you have a chill day. Have a rest :)")
        exit(0)
    for i in range(times):
        name = input("Name: ")
        start = input("Start at (HH:MM): ")
        start_minutes = get_time(start)
        duration = input("Duration (HH:MM): ")
        duration_minutes = get_time(duration)
        case = {
            "Name": name,
            "Start": start_minutes,
            "Duration": duration_minutes
        } 
        pickle.dump(case, file)
    file.close()

def time_out(string, hours, minutes):
    print(string, ": 0" if (hours < 10) else ": ", hours, end = '', sep = '')
    print(":0" if (minutes < 10) else ":", minutes, sep = '')

def file_output(file_name):
    print('\n', "-" * 20, sep = '')
    print('\n', file_name, '\n', sep = '')

    with open(file_name, 'rb') as file:
        size_file = file.seek(0, 2)
        file.seek(0)

        while file.tell() < size_file:
            case = pickle.load(file)
            print("Name of occasion:", case['Name'])
            time_out("Starts at", case['Start'] // 60, case['Start'] % 60)
            time_out("Duration", case['Duration'] // 60, case['Duration'] % 60)
            end_time = case['Start'] + case['Duration']
            time_out("End time", end_time // 60, end_time % 60)
            print()

    print("-" * 20, '\n')

def the_nearest_case(file_name):
    current_time = datetime.now()
    current_minutes = current_time.hour * 60 + current_time.minute
    nearest_minutes = 1440
    nearest_case = "All your occasions is over. Have a rest!\n"

    with open(file_name, 'rb') as file:
        size_file = file.seek(0, 2)
        file.seek(0)

        while file.tell() < size_file:
            new_case = pickle.load(file)
            temp_minutes = new_case['Start']

            if current_minutes <= temp_minutes and nearest_minutes >= temp_minutes:
                nearest_minutes = temp_minutes
                nearest_case = new_case['Name']
        if nearest_minutes != 1440:
            print("Your next occasion is -", nearest_case, end = '')
            time_out(" and it starts at", nearest_minutes // 60, nearest_minutes % 60)
            print()
        else:
            print(nearest_case)

def free_time(name_out, name_in):
    file_out = open(name_out, 'rb')
    size_file = file_out.seek(0, 2)
    file_out.seek(0)
    file_in = create_file(name_in)
    recursion(file_out, file_in, 780, 1440, 0, size_file)
    file_in.close()
    file_out.close()


def recursion(file_out, file_in, upper_border, lower_border, temp_byte, size_file):
    if temp_byte >= size_file:
        time = {
            'Start': upper_border,
            'End': lower_border,
            'Duration': lower_border - upper_border
        }
        pickle.dump(time, file_in)
    else:
        case = pickle.load(file_out)
        temp_byte = file_out.tell()
        start_time = case['Start']
        end_time = case['Start'] + case['Duration']

        if start_time <= upper_border and end_time < lower_border and end_time > upper_border:
            upper_border = end_time
            recursion(file_out, file_in, upper_border, lower_border, temp_byte, size_file)

        elif start_time > upper_border and end_time >= lower_border and start_time < lower_border:
            lower_border = start_time
            recursion(file_out, file_in, upper_border, lower_border, temp_byte, size_file)

        elif start_time > upper_border and end_time < lower_border:
            position = file_out.tell()
            recursion(file_out, file_in, upper_border, start_time, temp_byte, size_file)
            file_out.seek(position)
            recursion(file_out, file_in, end_time, lower_border, temp_byte, size_file)

        elif (start_time < upper_border and end_time <= upper_border) or (start_time >= lower_border and end_time > lower_border):
            recursion(file_out, file_in, upper_border, lower_border, temp_byte, size_file)

        elif start_time <= upper_border and end_time >= lower_border:
            return

        else:
            print("Something went wrong :(\nCheck your input data")
            exit(0)

def b_file_output(file_name):
    print('\n', "-" * 20, sep = '')
    print('\n', file_name, '\n', sep = '')

    with open(file_name, 'rb') as file:
        size_file = file.seek(0, 2)
        file.seek(0)

        while file.tell() < size_file:
            time = pickle.load(file)
            time_out("Free time starts at", time['Start'] // 60, time['Start'] % 60)
            time_out("Ends at", time['End'] // 60, time['End'] % 60)
            time_out("Duration", time['Duration'] // 60, time['Duration'] % 60)
            print()

    print("-" * 20, '\n')
