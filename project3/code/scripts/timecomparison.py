"""
Author: Sigurd Sandvoll Sundberg

This is spesifically designed to plot the time difference between the different solvers for
eigenvalue problems for the buckling beam problem.
Can be used on any problem with runs with different gridpoints and fixed extreme values.
"""

import numpy as np
import matplotlib.pyplot as plt
from itertools import groupby
import os
import sys


plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
# plt.rc('text', usetex=True)

# problem = sys.argv[1]

problem_list = ["Time_comp_Eul", "Time_comp_Ver"]
# Absolute path
path = "../classes/Data/Timing/"

# Relative path
# path = "./classes/Data/Timing/"


def read_file(path):
    """Spesific function for reading a spesific data file
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return [data[:, 0], np.log10(data[:, 1])]


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


N, E = read_file(path + problem_list[0])
_, V = read_file(path + problem_list[1])


permute = N.argsort()
N = N[permute]
E = E[permute]
V = V[permute]


# x
key = np.array([key for key, _ in groupby(N)])

# y
E_mean = get_mean(N, E)
V_mean = get_mean(N, V)


E_m, E_b = fit(key, E_mean)
V_m, V_b = fit(key, V_mean)


key_fit = np.insert(key, 0, 0.8)

E = g(key_fit, E_m, E_b)
V = g(key_fit, V_m, V_b)


E_err = max_error(E, E_mean)
V_err = max_error(V, V_mean)


plt.plot(key_fit, E, "r--", label=r"$\log10(s)$ Forward Euler")
plt.plot(key_fit, V, "b-.", label=r"$\log10(s)$ Velocity Verlet")
plt.plot(key_fit, E, 'o')
plt.plot(key_fit, V, 'o')


plt.errorbar(key, V_mean, yerr=V_err,
             fmt="ro", markersize=4,  barsabove=True, label="Datapoints Velocity Verlet", capsize=3, elinewidth=2)
plt.errorbar(key, E_mean, yerr=E_err,
             fmt="go", markersize=4,  barsabove=True, label="Datapoints Armadillo", capsize=3, elinewidth=2)
plt.legend()
plt.xlabel(r"$\log_{10}(10^{n}) \,[s]$")
plt.ylabel(r"$\log_{10}(t) \,[s]$")  # Time
plt.title("Log/Log plot of time vs gridpoints")
plt.annotate(
    fr"Forward Euler: gradient = {E_m:.2f}$\pm${E_err:.2f}", [4, -5])
plt.annotate(
    fr"Velocity Verlet: gradient = {V_m:.2f}$\pm${V_err:.2f}", [4, -4.6])
plt.show()
