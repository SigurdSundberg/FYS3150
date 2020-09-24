import numpy as np
import matplotlib.pyplot as plt
from itertools import groupby
import os
import sys


# plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
plt.rc('text', usetex=True)

path = "../data/time_Comparison_BB"


def read_file(path):
    """Spesific function for reading a spesific data file 
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return np.log10([data[:, 0], data[:, 1], data[:, 2], data[:, 3]])


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


def get_mean(N, M):
    # Number of each item in the sorted list []
    k = [len(list(group)) for _, group in groupby(N)]
    n = k[0]
    c = 0
    M_tmp = []
    M_merr = []
    for _ in range(len(k)):
        for _ in range(n):
            M_tmp.append(M[c])
            c += 1
        M_merr.append(np.array(M_tmp).mean())
        M_tmp = []
    return np.array(M_merr)


N, A, J, B = read_file(path)
permute = N.argsort()
N = N[permute]
A = A[permute]
J = J[permute]
B = B[permute]

# x
key = np.array([key for key, _ in groupby(N)])

# y
A_mean = get_mean(N, A)
J_mean = get_mean(N, J)
B_mean = get_mean(N, B)

A_m, A_b = fit(key, A_mean)
J_m, J_b = fit(key, J_mean)
B_m, B_b = fit(key, B_mean)

key_fit = np.insert(key, 0, 0.8)

A = g(key_fit, A_m, A_b)
J = g(key_fit, J_m, J_b)
B = g(key_fit, B_m, B_b)

A_err = max_error(A, A_mean)
J_err = max_error(J, J_mean)
B_err = max_error(B, B_mean)

plt.plot(key_fit, A, "k--", label=r"$\log10(t)$ Armadillo")
plt.plot(key_fit, J, "k", label=r"$\log10(t)$ Jacobi")
plt.plot(key_fit, B, "k-.", label=r"$\log10(t)$ Bisection")

plt.errorbar(key, J_mean, yerr=J_err,
             fmt="ro", markersize=4,  barsabove=True, label="Datapoints Jacobi", capsize=3, elinewidth=2)
plt.errorbar(key, A_mean, yerr=A_err,
             fmt="go", markersize=4,  barsabove=True, label="Datapoints Armadillo", capsize=3, elinewidth=2)
plt.errorbar(key, B_mean, yerr=B_err,
             fmt="mo", markersize=4,  barsabove=True, label="Datapoints Bisection", capsize=3, elinewidth=2)
plt.legend()
plt.xlabel(r"$\log_{10}(n)$")
plt.ylabel(r"$\log_{10}(t)$")  # Time
plt.title("Log/Log plot of time vs gridpoints")
plt.annotate(fr"Armadillo: m = {A_m:.2f}$\pm${A_err:.2f}", [0.75, -1])
plt.annotate(fr"Jacobi: m = {J_m:.2f}$\pm${J_err:.2f}", [0.75, -1.33])
plt.annotate(fr"Bisection: m = {B_m:.2f}$\pm${B_err:.2f}", [0.75, -1.66])
plt.savefig("../BB_plot/timecomp.pdf")
plt.show()
