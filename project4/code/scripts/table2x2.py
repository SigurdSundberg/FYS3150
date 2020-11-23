from math import cosh, sinh, exp
import numpy as np

""" 
This file is meant to read input data from the cpp function output
The filename has to be on the following format
    >>> filename = [relative path][filename]
with expects two files, examples seen below.
This is the data included in data folder under 2x2
"""
# *******************************************
# Only edit the variable filename
filenames = ["../cpp/data/2x2/ordered2", "../cpp/data/2x2/unordered2"]
# *******************************************


T = 1


def readFile(filename):
    # MCs E Cv M X absM
    data = np.loadtxt(filename)
    return [data[0][1], data[0][5], data[0][2], data[0][4]], [data[1][1], data[1][5], data[1][2], data[1][4]], [data[2][1], data[2][5], data[2][2], data[2][4]], [data[3][1], data[3][5], data[3][2], data[3][4]]


def createTable(kwargs, file1, file2, file3, file4):
    n = "\n"
    filename = "../../report/table" + str(kwargs[0])
    with open(filename, 'w') as o:
        o.write(r"\begin{table}" + n)
        o.write(r"\centering" + n)
        o.write(r"\caption{}" + n)
        o.write(r"\label{tab:table" + rf"{str(kwargs[0]):s}" + r"}" + n)
        o.write(r"\begin{tabular}{|c|c|c|c|c|}" + n)
        o.write(r"\hline" + n)
        o.write(r"$\log_{10}(t)$ & $\langle E \rangle / L^2$ & $\langle \abs{M}\rangle / L^2$ & $C_v/L^2$ & $\mathcal{X}/L^2$\\" + n)
        o.write(r"\hline" + n)
        o.write(rf"3.0 & {file1[0]:.6f} &{file1[1]:.6f} &{file1[2]:.6f} &{file1[3]:.6f} \\" + n)
        o.write(rf"4.0 & {file2[0]:.6f} &{file2[1]:.6f} &{file2[2]:.6f} &{file2[3]:.6f} \\" + n)
        o.write(rf"5.0 & {file3[0]:.6f} &{file3[1]:.6f} &{file3[2]:.6f} &{file3[3]:.6f} \\" + n)
        o.write(rf"6.0 & {file4[0]:.6f} &{file4[1]:.6f} &{file4[2]:.6f} &{file4[3]:.6f} \\" + n)
        o.write(r"\hline" + n)
        o.write(r"$\infty$" + rf"& {kwargs[1]:.6f} & {kwargs[2]:.6f} & {kwargs[3]:.6f} & {kwargs[4]:.6f}\\" + n)
        o.write(r"\hline" + n)
        o.write(r"\end{tabular}" + n)
        o.write(r"\end{table}" + n)


beta = 1
Z_a = 4 * (3 + np.cosh(8 * beta))
E = -32 * np.sinh(8 * beta) / Z_a / 4
EE = 256 * np.cosh(8 * beta) / Z_a / 4
absM = 8 * (np.exp(8 * beta) + 2) / Z_a / 4
absMM = (32 * np.exp(8 * beta) + 32) / Z_a
X = (absMM - (4 * absM)**2) / 1 / 4
Cv = (256 * np.cosh(8) - 32**2 * (np.sinh(8))**2 / Z_a) / Z_a / 4


for order in filenames:
    file1, file2, file3, file4 = readFile(order)
    createTable([order.split("/")[-1][:-1], E, absM, Cv, X], file1, file2, file3, file4)
