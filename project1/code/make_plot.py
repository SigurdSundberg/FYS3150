import matplotlib.pyplot as plt
import numpy as np
import sys
import os.path


def plot_file(in_file):
    [x, app, *_] = read_file4(in_file)
    plt.plot(x, app, '--', label=f"n = 10^{in_file[-1]:s}")


def read_file4(in_file):
    if not os.path.isfile("./output/" + in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt("./output/" + in_file, skiprows=skip_rows)
        return [data[:, 0], data[:, 1], data[:, 2], data[:, 3]]


def setup_figure():
    plt.figure()


def finalize_figure(in_file, out_file):
    plt.legend()
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.title(f"Analytical solution plotted against {in_file:s} method")
    plt.savefig("./plots/" + out_file)


try:
    in_file = sys.argv[1]
    number_of_files = int(sys.argv[2])
except:
    print("input name of file and number of files you want to run\n")
out_file = in_file
skip_rows = 2
setup_figure()
# To plot the best fit curve for the exact values
x, _, exact, _ = read_file4(in_file + str(number_of_files))
plt.plot(x, exact, 'k', label="Analytical", linewidth=2)
for i in range(1, number_of_files + 1):
    in_file_i = in_file + str(i)
    plot_file(in_file_i)
finalize_figure(in_file, "plot_" + out_file)
