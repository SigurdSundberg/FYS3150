import numpy as np
import sys
import os.path


def read_file(in_file):
    if not os.path.isfile("./output/" + in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt("./output/" + in_file, skiprows=skip_rows)
        return float(data)


def write_to_file(out_file, input, n=False):
    with open('./output/' + out_file + ".txt", 'a+') as o:
        o.write(f"{n:4d} | {input:15.8f}\n")


def create_time_table(in_file, out_file, i):
    data = read_file(in_file)
    write_to_file(out_file, data, i)


def setup_table(in_file):
    with open('./output/timed_' + in_file + ".txt", 'w') as o:
        o.write("Time table for  " + in_file + " in seconds\n")


try:
    in_file = sys.argv[1]
    number_of_files = int(sys.argv[2])
except:
    print("Problem in " + sys.argv[0] +
          f"with input {in_file} or {number_of_files}")

# this value could've been hardcoded into the text files as first argument or in the name.
skip_rows = 2
# Create a new file each time this is ran, and append values.
setup_table(in_file)
in_file = "timed_" + in_file
for i in range(1, number_of_files+1):
    in_file_i = in_file + str(i)
    create_time_table(in_file_i, in_file, i)
