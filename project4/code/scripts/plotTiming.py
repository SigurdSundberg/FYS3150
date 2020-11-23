import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

""" 
This file is meant to read input data from the cpp function outputTime
The filename has to be on the following format
    >>> filename = [relative path][filename]["Normal"/"Para"]_[compilerflag]_[dim]
with 
    >>> compilerflag = ["", "-O2", "-O3", "-Ofast"]
    >>> dim = [20, 40, 60, 80, 100]
"""
# *******************************************
# Only edit the variable filename
filename = "../cpp/data/time/Timing"
# *******************************************

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]}
)


program = ["Normal", "Para"]
compilerFlags = ["", "-O2", "-O3", "-Ofast"]
dim = [20, 40, 60, 80, 100]


def readFile(filename):
    return np.loadtxt(filename)


c = {
    "": "g",
    "-O2": "r",
    "-O3": "b",
    "-Ofast": "k"
}
fig, ax = plt.subplots()
for flag in compilerFlags:
    time1 = []
    time2 = []
    for d in dim:
        dataNorm = np.loadtxt(path + program[0] + "_" + flag + "_" + str(d))
        dataPara = np.loadtxt(path + program[1] + "_" + flag + "_" + str(d))
        time1.append(np.mean(dataNorm))
        time2.append(np.mean(dataPara))
    if flag == "":
        flag1 = "No flag (Unparallelized)"
        flag2 = "No flag"
        marker1 = "2"
        marker2 = "1"
        markersize = 80
    else:
        flag1 = flag + " (Unparallelized)"
        flag2 = flag
        marker1 = 6
        marker2 = 7
        markersize = 40
    ax.scatter(dim, np.log10(np.array(time1)), marker=marker1, label=rf"{flag1:s}", s=markersize, c=c[flag])
    ax.scatter(dim, np.log10(np.array(time2)), marker=marker2, label=rf"{flag2:s}", s=markersize, c=c[flag])
ax.set_title(r"Timing over 100000 Monte Carlo cycles")
ax.set_xlabel(r"Lattice size [LxL]")
ax.set_ylabel(r"$\log_{10}(t)[s]$")
ax.legend()

plt.show()
