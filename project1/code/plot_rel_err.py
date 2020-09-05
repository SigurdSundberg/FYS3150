import matplotlib.pyplot as plt
import numpy as np
import sys
import os.path


def plot_file(in_file):
    [h, k] = read_file(in_file)
    plt.plot(h, k, "k")


def read_file(in_file):
    if not os.path.isfile("./output/" + in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt("./output/" + in_file,
                          skiprows=skip_rows, usecols=(0, 2))
        return [data[:, 0], data[:, 1]]


def setup_figure():
    plt.figure()


def finalize_figure(in_file, out_file):
    # plt.legend()
    plt.xlabel("log10(h)")
    plt.ylabel("log10(relative error)")
    plt.title(f"Log/Log plot for {out_file[6::]} method")
    plt.savefig("./plots/" + out_file)


try:
    in_file = sys.argv[1]
    number_of_files = int(sys.argv[2])
except:
    print("Input filename and number of files\n")
out_file = in_file
skip_rows = 1
setup_figure()
in_file = "error_" + in_file + ".txt"
plot_file(in_file)
finalize_figure(in_file, "error_" + out_file)
