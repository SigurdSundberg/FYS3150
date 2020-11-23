import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

""" 
This file is meant to read input data from the cpp function output 3
Define a filename of the relative path to the data file. It has to be on the format of 
    >>> filename = [Relative path][filename][runs][dim]
for it to be read by the program. 
It expects a total of 2 files, with 
    >>> runs = ["1","2"]
    >>> dim = "20"
"""
# *******************************************
# Only edit the variable filename
filename = "../cpp/data/probability/prob"
# *******************************************

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]}
)

dim = "20"
runs = ["1", "2"]


def readFile(filename):
    return np.loadtxt(filename)


run1 = readFile(filename + runs[0] + dim)
run2 = readFile(filename + runs[1] + dim)
fig, [ax1, ax2] = plt.subplots(nrows=1, ncols=2, constrained_layout=True)
ax1.hist(run1, bins=10, density=True, ec='black', histtype='bar')
ax1.set_xlabel("$E/J$", size=16)
ax1.set_ylabel("$P(E)$", size=16)
ax1.tick_params(size=16)
ax1.set_xlim((-800, -760))
ax1.set_title(r"Probability distribution for T = 1.0")
ax2.hist(run2, bins=200, density=True, ec='black', histtype='bar')
ax2.set_xlabel("$E/J$", size=16)
ax2.set_ylabel("$P(E)$", size=16)
ax2.tick_params(size=16)
ax2.set_xlim((-760, -220))
ax2.set_title(r"Probability distribution for T = 2.4")
plt.show()

print(np.mean(run1))
print(np.mean(run2))
