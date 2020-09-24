import matplotlib.pyplot as plt
import numpy as np
import os.path
import sys

plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
plt.rc('text', usetex=True)

path1 = "../data/time_iterations_ja_BB"
path2 = "../data/time_iterations_bi_BB"


def read_file(path):
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


x, y = read_file(path1)
_, y2 = read_file(path2)
x = np.log10(x)
y = np.log10(y)
y2 = np.log10(y2)
m, b = fit(x, y)
m2, b2 = fit(x, y2)

num_values = g(x, m, b)
num_values2 = g(x, m2, b2)

plt.plot(x, num_values, "k", label="Jacobi: $\log_{10}(I)$")
plt.plot(x, num_values2, "r", label="Bisection: $\log_{10}(I)$")

plt.errorbar(x, y, yerr=max_error(num_values, y),
             fmt="o", markersize=1,  barsabove=True, label="Datapoints Jacobi", capsize=3, elinewidth=2)
plt.errorbar(x, y2, yerr=max_error(num_values2, y2),
             fmt="ko", markersize=1,  barsabove=True, label="Datapoints Bisection", capsize=3, elinewidth=2)

plt.xlabel("$\log_{10}(n)$")
plt.ylabel("$\log_{10}(I)$")  # Iterations
plt.title("Log/Log plot of iterations vs gridpoints")

plt.annotate(
    fr"Maximum error Jacobi: $\pm${max_error(num_values,y):.3f}", [1, 5.5])
plt.annotate(fr"Jacobi: m = {m:.3f}", [1, 5.25])
plt.annotate(
    fr"Maximum error Bisection: $\pm${max_error(num_values2,y2):.3f}", [1, 5.0])
plt.annotate(fr"Bisection: m = {m2:.3f}", [1, 4.75])

plt.legend(loc=4)
plt.savefig("../BB_plot/n_iter.pdf")
# plt.show()
