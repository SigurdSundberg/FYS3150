# Plotting for number of accepted states for the 20x20 lattice
# For different values of T
# Also plotting of the energy and mean magnetization against time
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]})

orderList = ["0", "1"]
tempList = ["1", "2.4"]
E = []
M = []
A = []
for tInitial in tempList:
    for order in orderList:
        a = []
        m = []
        e = []
        filename = "../cpp/data/LatticeEquil_"
        filename += order + "_" + tInitial + "_20"
        with open(filename, 'r') as f:
            for line in f:
                line = line.split()
                e.append(float(line[3]))
                m.append(float(line[4]))
                a.append(float(line[2]))
        E.append(e)
        M.append(m)
        A.append(a)
plt.plot(E[0][:])
plt.plot(E[1][:])
plt.plot(E[2][:])
plt.plot(E[3][:])
plt.show()
plt.plot(A[0][:])
plt.plot(A[1][:])
plt.plot(A[2][:])
plt.plot(A[3][:])
plt.show()
plt.plot(M[0][:])
plt.plot(M[1][:])
plt.plot(M[2][:])
plt.plot(M[3][:])
plt.show()
