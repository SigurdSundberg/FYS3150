from math import cosh, sinh, exp
import numpy as np


""" 
This file is meant to read input data from the cpp function output
The filename has to be on the following format
    >>> filename = [relative path][filename]
with expects two files, examples seen below.
"""
# *******************************************
# Only edit the variable filename
filenames = ["../cpp/data/probability/var120", "../cpp/data/probability/var220"]
# *******************************************

T = 1


def readFile(filename):
    # T E Cv M X absM
    data = np.loadtxt(filename)
    return [np.sqrt(data[0][2] * 20 * 20), np.sqrt(data[1][2] * 20 * 20 * 2.4**2)]


def createTable(kwargs, file1, file2):
    n = "\n"
    filename = "../../report/figures/tableVar" + str(kwargs[0])
    with open(filename, 'w') as o:
        o.write(r"\begin{table}" + n)
        o.write(r"\centering" + n)
        o.write(r"\caption{}" + n)
        o.write(r"\label{tab:table" + rf"{str(kwargs[0]):s}" + r"}" + n)
        o.write(r"\begin{tabular}{|c|c|c|}" + n)
        o.write(r"\hline" + n)
        o.write(r"$T$ & $\sigma_E$(Ground state initiation) & $\sigma_E$(Random initiation)\\" + n)
        o.write(r"\hline" + n)
        o.write(rf"1.0 & {file1[0]:.6f} &{file2[0]:.6f}\\" + n)
        o.write(rf"2.4 & {file1[1]:.6f} &{file2[1]:.6f}\\" + n)
        o.write(r"\hline" + n)
        o.write(r"\end{tabular}" + n)
        o.write(r"\end{table}" + n)


file1 = readFile(filenames[0])
file2 = readFile(filenames[1])
createTable([T], file1, file2)
