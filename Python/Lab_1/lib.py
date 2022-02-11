def init_file(name):
    print("How you want to add text\n1) append to existing file \n2) create new")
    while (True):
        how_open = int(input("Choose 1 or 2: "))
        if how_open == 1:
            file = open(name, "at")
            break
        elif how_open == 2:
            file = open(name, "wt")
            break
        else:
            print("Incorrect input. Try again")
    print("Input your text\nPress ENTER to begin new line and press CTRL+Z to finish")
    if (file):
        while True:
            line = input()
            if (line.find(chr(26)) != -1):
                file.write(line[0:-1] + '\n')
                break
            else:
                file.write(line + '\n')
        file.close()
    else:
        print("initFile.txt couldn't be opened")
        exit(1)

def edit_file(name1, name2):
    input_file = open(name1, "rt")
    output_file = open(name2, "wt")
    for line in input_file:
        line = line.rstrip()
        last_space = line.rfind(" ")
        if (last_space != -1 or line):
            newLine = line[last_space + 1] + " - " + line
            output_file.write(newLine + '\n')
        elif not line:
            newLine = " - "
            output_file.write(newLine + '\n')
    input_file.close()
    output_file.close()

def out_file(name):
    file = open(name, "rt")
    print(file.read())
    file.close()