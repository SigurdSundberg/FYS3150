import numpy as np
import matplotlib.pyplot as plt
import sys
import os

path = "../cpp_codes/output/data_BB"

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


def eigenvector(l, n):
    v = np.zeros(n)
    for j in range(n):
        v[j] = np.sin(((l+1)*(j+1)*np.pi)/(n+1))
    return v


n = 200
data = read_file(path + str(n))
values = data[0, :]
vectors = data[1::, :]
permute = values.argsort()
colors = ["m", "k", "g"]
for j in range(3):
    vector = vectors[:, permute][:, j]
    x = np.linspace(0, 1, n)
    v = eigenvector(j, n)
    relation = v[0]/vector[0]
    plt.plot(x, v, color=colors[j], linewidth=2,
             label=fr"Analytical: $\lambda_{j+1:d}$")
    plt.plot(x, (vector*relation*0.9), colors[j] + "-.",
             label=fr"Numerical: $\lambda_{j+1:d}$")
plt.title(r"Three first eigenvectors for corresponding $\lambda_{i}$")
plt.xlabel(r"$\rho$")
plt.ylabel(r"$u(\rho)$")
plt.legend()
plt.savefig("../BB_plot/eigenvec.pdf")
# plt.show()
