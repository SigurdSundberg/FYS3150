import numpy as np
import sys
import os.path


def find_max_relative_error(in_file, out_file, i):
    [*_, rel] = read_file4(in_file)
    max_value = max(rel)
    write_to_file(out_file, max_value, i)


def read_file4(in_file):
    if not os.path.isfile("./output/" + in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt("./output/" + in_file, skiprows=skip_rows)
        return [data[:, 0], data[:, 1], data[:, 2], data[:, 3]]


def write_to_file(out_file, input, i=False):
    with open('./output/' + out_file + ".txt", 'a+') as o:
        if isinstance(input, (float, int)):
            o.write(f"{i:4d} | {input:15.8f}\n")
        else:
            for ele in input:
                o.write(f"{ele:15.8f}\n")


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
with open('./output/error_' + in_file + ".txt", 'w') as o:
    o.write("Error for " + in_file + "\n")
for i in range(1, number_of_files+1):
    in_file_i = in_file + str(i)
    find_max_relative_error(in_file_i, "error_" + in_file, i)
