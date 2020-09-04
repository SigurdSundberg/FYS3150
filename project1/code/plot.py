#!/usr/bin python3
import matplotlib.pyplot as plt
import numpy as np
import sys
import os.path


def plot_file(in_file):
    [x, app, *_] = read_file4(in_file)
    plt.plot(x, app, '--', label=f"n = {in_file[-1]:s}")


def find_max_relative_error(in_file, out_file):
    [*_, rel] = read_file4(in_file)
    max_value = max(rel)
    write_to_file(out_file, max_value)


def read_file4(in_file):
    if not os.path.isfile("./output/" + in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt("./output/" + in_file, skiprows=skip_rows)
        return [data[:, 0], data[:, 1], data[:, 2], data[:, 3]]


def write_to_file(out_file, input):
    with open('./output/' + out_file + ".txt", 'a+') as o:
        if isinstance(input, (float, int)):
            o.write(f"{input:15.8f}\n")
        else:
            for ele in input:
                o.write(f"{ele:15.8f}\n")


def setup_figure():
    plt.figure()


def finalize_figure(in_file, out_file):
    plt.legend()
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.title(f"Analytical plotted against {in_file:s} method")
    plt.savefig("./plots/" + out_file)


if __name__ == "__main__":
    try:
        arg = sys.argv[1]
        in_file = sys.argv[2]
        number_of_files = int(sys.argv[3])
    except:
        print("Wrong use: include infile, outfile, number of files and number of rows to skip\n")
    out_file = in_file
    skip_rows = 2
    if arg == "plot":
        setup_figure()
        # To plot the best fit curve for the exact values
        x, _, exact, _ = read_file4(in_file + str(number_of_files))
        plt.plot(x, exact, 'k', label="Analytical", linewidth=2)
        for i in range(1, number_of_files+1):
            in_file_i = in_file + str(i)
            plot_file(in_file_i)
            print("Success")
        finalize_figure(in_file, "plot_" + out_file)
    elif arg == "rel":
        with open('./output/error_' + out_file + ".txt", 'w') as o:
            o.write("Error for " + in_file + "\n")
        for i in range(1, number_of_files+1):
            in_file_i = in_file + str(i)
            find_max_relative_error(in_file_i, "error_" + out_file)
            print("Success")
    else:
        print(
            "No argument was given, either use 'rel' or 'plot' to specify what the functions should do \n")
        exit(1)

print("Exit")

"""
Run example 
python3 plot.py plot specialized plot_specialized 3 2 
"""
