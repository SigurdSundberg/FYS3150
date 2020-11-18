import numpy as np
import matplotlib.pyplot as plt
import sys

# filename = argv[1]
filename = "../cpp/data/Lattice20/test20"


def readFile(filename):
    e = []
    m = []
    cv = []
    x = []
    t = []
    with open(filename, 'r') as f:
        p = f.readline()
        print(p)
        for line in f:
            line = line.split()
            t.append(float(line[0]))
            e.append(float(line[1]))
            m.append(float(line[5]))
            cv.append(float(line[2]))
            x.append(float(line[4]))
    return (t, e, m, cv, x)


t, e, m, cv, x = readFile(filename)
T = np.array(t)
E = np.array(e)
M = np.array(m)
Cv = np.array(cv)
X = np.array(x)

plt.plot(T, E)
plt.show()
plt.plot(T, M)
plt.show()
plt.plot(T, Cv)
plt.show()
plt.plot(T, X)
plt.show()
