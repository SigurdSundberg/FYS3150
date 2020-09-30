"""
Author: Sigurd Sandvoll Sundberg

This is plots the eigenvectors of the three lowest eigenvalues against their analytical solutions.
The plot is spesific to the Buckling Beam problem, but with small modifications
can plot any number of eigenvalues.
"""

import numpy as np
import matplotlib.pyplot as plt
import sys
import os


problem = sys.argv[1]
n = sys.argv[2]
largest_eigenvalue = int(sys.argv[3])

path = "./cpp_codes/output/data_" + problem + n

n = int(n)


def read_file(path):
    """Spesific function for reading a spesific data file
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return data


def eigenvector(l, n):
    """Analytical eigenvalues

    Args:
        l (int): current eigenvalue
        n (int): number of elements in eigenvector

    Returns:
        vector: analytic eigenvalues
    """
    v = np.zeros(n)
    for j in range(n):
        v[j] = np.sin(((l+1)*(j+1)*np.pi)/(n+1))
    return v


data = read_file(path)
values = data[0, :]
vectors = data[1::, :]
permute = values.argsort()
colors = ["m", "k", "g"]
for j in range(largest_eigenvalue):
    vector = vectors[:, permute][:, j]
    x = np.linspace(0, 1, n)
    # Comment out this line if you want to plot only the numerical eigenvectors
    v = eigenvector(j, n)
    # Comment out this line if you want to plot only the numerical eigenvectors
    relation = v[0]/vector[0]
    # Comment out this line if you want to plot only the numerical eigenvectors
    plt.plot(x, v, color=colors[j], linewidth=2,
             label=fr"Analytical: $\lambda_{j+1:d}$")
    # And uncomment the following line
    # relation = 10/9
    plt.plot(x, (vector*relation*0.9), colors[j] + "-.",
             label=fr"Numerical: $\lambda_{j+1:d}$")
plt.title(r"Three first eigenfunctions for corresponding $\lambda_{i}$")
plt.xlabel(r"$\rho$")
plt.ylabel(r"$u(\rho)$")
plt.legend()
plt.savefig("./BB_plot/eigenvec.pdf")
plt.show()
