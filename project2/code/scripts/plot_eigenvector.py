import numpy as np
import matplotlib.pyplot as plt
import sys
import os


path = "../cpp_codes/output/data_BB200"

# [10, 25, 75, 100, 150, 200, 300, 500]


def read_file(path):
    """Spesific function for reading a spesific data file 
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path)
        return data


def eigenvector():
    """Creates the problem which is solved in cpp, and finds the "analytical" solutions 
    by using numpys eigen solver for the eigenvectors. 
    """
    n = 200
    h = 1/(n+1)
    diag = 2/(h*h)
    non_diag = -1/(h*h)
    A = np.zeros((n, n))
    A[0, 0] = diag
    A[0, 1] = non_diag
    for i in range(1, n-1):
        A[i, i] = diag
        A[i, i-1] = non_diag
        A[i, i+1] = non_diag
    A[n-1, n-1] = diag
    A[n-1, n-2] = non_diag

    values, vectors = np.linalg.eig(A)
    permute = values.argsort()
    vectors = vectors[:, permute]
    v = vectors[0]
    return v


data = read_file(path)
values = data[:, 0]
vectors = data[:, 1::]
permute = values.argsort()
vector = vectors[permute, :][0]
# plt.savefig("../BB_plot/eigenvec.pdf")
# plt.show()
