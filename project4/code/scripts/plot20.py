# Plotting for number of accepted states for the 20x20 lattice
# For different values of T
# Also plotting of the energy and mean magnetization against time
import numpy as np
import matplotlib.pyplot as plt

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]})

orderList = ["0", "1"]
tempList = ["1", "2.4"]
fig, axE = plt.subplots()
fig, axM = plt.subplots()
fig, axA = plt.subplots()
argsOrder = {
    "0": "ordered",
    "1": "unordered"
}
argsTemp = {
    "1": 1,
    "2.4": 2.4
}
for tInitial in tempList:
    for order in orderList:
        MCs = []
        a = []
        m = []
        e = []
        filename = "../cpp/data/20x20/LatticeEquil_"
        filename += order + "_" + tInitial + "_20"
        with open(filename, 'r') as f:
            for line in f:
                line = line.split()
                MCs.append(float(line[1]))
                e.append(float(line[3]))
                m.append(float(line[4]))
                a.append(float(line[2]))

        axE.plot(MCs, e, label=rf"T = {argsTemp[tInitial]:.1f}J/$k_B$ {argsOrder[order]:s}")
        axM.plot(MCs, m, label=rf"T = {argsTemp[tInitial]:.1f}J/$k_B$ {argsOrder[order]:s}")
        axA.plot(MCs, a, label=rf"T = {argsTemp[tInitial]:.1f}J/$k_B$ {argsOrder[order]:s}")
axE.set_xscale("log")
axE.set_xlabel(r"MC cycles")
axE.set_ylabel(r"$\langle E \rangle$ [J]")
axE.set_title(r"Mean Energy Equilibration")
axE.legend()

axM.set_xscale("log")
axM.set_xlabel(r"MC cycles")
axM.set_ylabel(r"$\langle |M| \rangle$")
axM.set_title(r"Mean Magnetization Equilibration")
axM.legend()

axA.set_xscale("log")
axA.set_yscale("log")
axA.set_xlabel(r"MC cycles")
axA.set_ylabel(r"Accepted spin-flips")
axA.set_title(r"Accepted spin-flips for different temperatures")
axA.legend()
plt.show()
