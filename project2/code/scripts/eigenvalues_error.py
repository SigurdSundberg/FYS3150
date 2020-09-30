"""
Author: Sigurd Sandvoll Sundberg

Finds the best approximation of the analytical eigenvalues
with different values of rho and n.

This code is an utter mass, please be excused. It does what it needs to and that is it.
"""

import numpy as np
import matplotlib.pyplot as plt
import sys
import os
from itertools import groupby

problem = sys.argv[1]
tol = int(sys.argv[2])
# problem = "QD_oneElectron"
path = "./cpp_codes/output/"
problem = "data_" + problem
path_general = "./GEN_data/"


def get_directory(path, problem):
    dirs = os.listdir(path)
    directory = []
    for _dir in dirs:
        if (problem in _dir):
            directory.append(_dir.strip(problem))
    return directory


def read_file(path):
    """Spesific function for reading a spesific data file
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path, max_rows=1)
        return data


analytical_eigenvalues = [3, 7, 11, 15]

directory = get_directory(path, problem)
directory.sort()
directory.sort(key=len, reverse=False)
directory = np.array(directory)

N = []
for element in directory:
    _, _x = element.split("_")
    N.append(float(_x))
N.sort()

pairs = []  # (rho,n)
counter = 0
tolerance = 10 ** (-tol)
for eigenvalue in analytical_eigenvalues:
    eigen = []
    for files in directory:
        file_path = path + problem + files
        data = read_file(file_path)
        data.sort()
        eigen.append(data[counter])
        if (abs(data[counter] - eigenvalue) < tolerance):
            break
    eigen = np.array(eigen)
    error = np.abs((eigen - eigenvalue)/eigenvalue)
    index = error.argmin()
    lowest_file = directory[index]
    rho, n = lowest_file.split("_")
    value = eigen[index]
    counter += 1

    pairs.append((float(rho)/10, int(n), value, directory[index]))
# pairs = [(rho, n, eigenvalue), (rho, n, eigenvalue)...]
with open(path_general + "eigenvalues_rho_n", 'w') as f:
    for elements in pairs:
        f.write(str(elements) + "\n")
