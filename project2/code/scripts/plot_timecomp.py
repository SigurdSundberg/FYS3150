import numpy as np
import matplotlib.pyplot as plt
from itertools import groupby
import os
import sys


# plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
plt.rc('text', usetex=True)

path = "../data/time_Comparison_BB.txt"


def read_file(path):
    """Spesific function for reading a spesific data file 
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return np.log10([data[:, 0], data[:, 1], data[:, 2]])


def max_error(num_values, y):
    max_error = 0
    for i, val in enumerate(y):
        current = abs(val - num_values[i+1])
        if max_error <= current:
            max_error = current
    return max_error
    # max_error = []
    # for i, val in enumerate(y):
    #     max_error.append(abs(val-num_values[i+1]))
    # return np.array(max_error)


def fit(x, y):
    return np.polyfit(x, y, 1)


def g(x, m, b):
    return m*x+b


def get_mean(N, A, J):
    # Number of each item in the sorted list []
    k = [len(list(group)) for _, group in groupby(N)]
    n = k[0]
    c = 0
    A_tmp = []
    J_tmp = []
    A_merr = []
    J_merr = []
    for _ in range(len(k)):
        for _ in range(n):
            A_tmp.append(A[c])
            J_tmp.append(J[c])
            c += 1
        A_merr.append(np.array(A_tmp).mean())
        J_merr.append(np.array(J_tmp).mean())
        A_tmp = []
        J_tmp = []
    return [np.array(A_merr), np.array(J_merr)]


N, A, J = read_file(path)
permute = N.argsort()
N = N[permute]
A = A[permute]
J = J[permute]

# x
key = np.array([key for key, _ in groupby(N)])

# y
A_mean = get_mean(N, A, J)[0]
J_mean = get_mean(N, A, J)[1]


A_m, A_b = fit(key, A_mean)
J_m, J_b = fit(key, J_mean)

key_fit = np.insert(key, 0, 0.8)

A = g(key_fit, A_m, A_b)
J = g(key_fit, J_m, J_b)

A_err = max_error(A, A_mean)
J_err = max_error(J, J_mean)

plt.plot(key_fit, A, "k--", label="$log10(t)$ Armadillo")
plt.plot(key_fit, J, "k", label="$log10(t)$ Jacobi")

plt.errorbar(key, J_mean, yerr=J_err,
             fmt="ro", markersize=4,  barsabove=True, label="Datapoints Jacobi", capsize=3, elinewidth=2)
plt.errorbar(key, A_mean, yerr=A_err,
             fmt="go", markersize=4,  barsabove=True, label="Datapoints Armadillo", capsize=3, elinewidth=2)
plt.legend()
plt.xlabel("$log_{10}n$")
plt.ylabel("$log_{10}t$")  # Time
plt.title("Log/Log plot of time vs gridpoints")
plt.annotate(fr"Armadillo: m = {A_m:.2f}$\pm${A_err:.2f}", [0.75, -1])
plt.annotate(fr"Jacobi: m = {J_m:.2f}$\pm${J_err:.2f}", [0.75, -2])
plt.savefig("../BB_plot/timecomp.pdf")
# plt.show()
