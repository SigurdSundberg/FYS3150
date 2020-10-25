import matplotlib.pyplot as plt
import numpy as np
from math import sqrt

plt.rcParams.update({
    "text.usetex": True,
    "font.sans-serif": ["Helvetica"],
    "font.family": "DejaVu Sans"})


# Absolute path
filename = []
for i in range(8):
    filename.append("../classes/Data/Stability/Edt" + str(i+1) + "Final.xyz")
    filename.append("../classes/Data/Stability/Vdt" + str(i+1) + "Final.xyz")

# Relative paths
# for i in range(8):
#     filename.append("./classes/Data/Stability/Edt" + str(i+1) + "Final.xyz")
#     filename.append("./classes/Data/Stability/Vdt" + str(i+1) + "Final.xyz")

# savefigPath = "./classes/figure/"
X = []
Y = []
Z = []
for e in filename:
    with open(e, 'r') as f:
        N = int(f.readline())
        string = f.readline()

        for line in f:
            line = line.split()
            Id = int(line[0])
            if Id == 2:
                X.append(float(line[1]))
                Y.append(float(line[2]))
                Z.append(float(line[3]))
rE = []
rV = []
algo = ["Forward Euler", "Velocity Verlet"]
timestep = [r"$10^{-1}$", r"$10^{-2}$", r"$10^{-3}$", r"$10^{-4}$",
            r"$10^{-5}$", r"$10^{-6}$", r"$10^{-7}$", r"$10^{-8}$"]

for i in range(len(X)):
    if (i % 2 == 0):
        rE.append(sqrt(X[i]**2 + Y[i]**2))
    else:
        rV.append(sqrt(X[i]**2 + Y[i]**2))

n = [1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8]

f, (ax, ax1) = plt.subplots(2, 1, sharex=True)
ax.set_title("Stability test of forward Euler vs velocity-Verlet")
ax.set_ylabel(r"Distance to Sun in [AU]")
ax1.set_ylabel(r"Distance to Sun in [AU]")
for i in range(8):
    ax.plot(np.log10(n[i]), rE[i], "go", label=algo[0] +
            rf" Time step = {timestep[i]:s}")
    ax.plot(np.log10(n[i]), rV[i], "ko", label=algo[1] +
            rf" Time step = {timestep[i]:s}")
    ax1.plot(np.log10(n[i]), rE[i], "go", label=algo[0] +
             rf" Time step = {timestep[i]:s}")
    ax1.plot(np.log10(n[i]), rV[i], "ko", label=algo[1] +
             rf" Time step = {timestep[i]:s}")

ax.set_ylim(46, 47)
ax1.set_ylim(0, 2.5)

ax.spines['bottom'].set_visible(False)
ax1.spines['top'].set_visible(False)
ax.xaxis.tick_top()
ax.tick_params(labeltop=False)  # don't put tick labels at the top
ax1.xaxis.tick_bottom()
d = .015  # how big to make the diagonal lines in axes coordinates
# arguments to pass to plot, just so we don't keep repeating them
kwargs = dict(transform=ax.transAxes, color='k', clip_on=False)
ax.plot((-d, +d), (-d, +d), **kwargs)        # top-left diagonal
ax.plot((1 - d, 1 + d), (-d, +d), **kwargs)  # top-right diagonal
kwargs.update(transform=ax1.transAxes)  # switch to the bottom axes
ax1.plot((-d, +d), (1 - d, 1 + d), **kwargs)  # bottom-left diagonal
ax1.plot((1 - d, 1 + d), (1 - d, 1 + d), **kwargs)  # bottom-right diagonal

plt.xlabel(r"Time step: $\log_{10}(10^{n}) [s]$")


plt.show()
