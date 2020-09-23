import matplotlib.pyplot as plt
import numpy as np
import os.path
import sys

plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
plt.rc('text', usetex=True)

path = "../data/time_iterations_BB"


def read_file():
    """Spesific function for reading a spesific data file 
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return [data[:, 0], data[:, 1]]


def max_error(num_values, y):
    max_error = 0
    for i, val in enumerate(y):
        current = abs(val - num_values[i])
        if max_error <= current:
            max_error = current
    return max_error


def fit(x, y):
    return np.polyfit(x, y, 1)


def g(x, m, b):
    return m*x+b


x, y = read_file()
x = np.log10(x)
y = np.log10(y)
m, b = fit(x, y)
num_values = g(x, m, b)

plt.plot(x, num_values, "k", label="$log_{10}(I)$")
plt.errorbar(x, y, yerr=max_error(num_values, y),
             fmt="o", markersize=1,  barsabove=True, label="Datapoints", capsize=3, elinewidth=2)
plt.xlabel("$log_{10}n$")
plt.ylabel("$log_{10}(I)$")  # Iterations
plt.title("Log/Log plot of iterations vs gridpoints")
plt.annotate(fr"Maximum error: $\pm${max_error(x,y):.3f}", [1, 4.5])
plt.annotate(fr"The incline is given by m = {m:.3f}", [1, 5.0])
plt.legend()
plt.savefig("../BB_plot/n_iter.pdf")
# plt.show()
