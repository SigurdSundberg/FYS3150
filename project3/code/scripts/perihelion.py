import numpy as np
import matplotlib.pyplot as plt
from math import pi

plt.rcParams.update({
    "text.usetex": True,
    "font.sans-serif": ["Helvetica"],
    "font.family": "DejaVu Sans"})

F1 = "../classes/Data/PPR.txt"
F2 = "../classes/Data/PPNR.txt"
r = []
nr = []

with open(F1, 'r') as f:
    f.readline()
    for line in f:
        r.append(float(line))
with open(F2, 'r') as f:
    f.readline()
    for line in f:
        nr.append(float(line))
r = np.array(r)
nr = np.array(nr)
arcsecond1 = abs(nr[-1] - r[-1])*3600 * 10 * 57.2957795
arcsecond2 = abs(-0.000320789 - (-0.00030013))*3600 * 10 * 57.2957795
print("Difference between the relativistic correction and non-relativistic corrention")
print(
    f"For a period of 10 years multiplied up to a century with dt = 10^-8 is: {arcsecond1:.3f}")
print(
    f"For the entire period of 100 years with a dt = 10^-7 it is: {arcsecond2:.3f}")


plt.plot(r*57.2957795*3600, 'o', label="Relativistic correction")
plt.plot(nr*57.2957795*3600, 'o', label="Non-relativistic correction")
plt.xlabel("Number of perihelion passes")
plt.ylabel("Perihelion precession [arc seconds]")
plt.title("Perihelion precession of Mercury")
plt.annotate(
    f"Final perihelion difference: {arcsecond1:.3f}[arc seconds]", (0, -60))
plt.legend()
plt.show()

""" 
Difference between the relativistic correction and non-relativistic corrention
Is given by: 42.612
"""
