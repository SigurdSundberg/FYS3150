import numpy as np
import matplotlib.pyplot as plt
import sys
from scipy.interpolate import UnivariateSpline
from scipy.optimize import curve_fit

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]})

# filename = argv[1]
filename = "../cpp/data/Lattice/lattice"
latticeSize = ["40", "60", "80", "100"]


def linear_func(x, a, b): return a + b * x  # Form of the function to fit.


def readFile(filename):
    e = []
    m = []
    cv = []
    x = []
    t = []
    with open(filename, 'r') as f:
        f.readline()
        for line in f:
            line = line.split()
            t.append(float(line[0]))
            e.append(float(line[1]))
            m.append(float(line[5]))
            cv.append(float(line[2]))
            x.append(float(line[4]))
    return (t, e, m, cv, x)


fig, [[ax1, ax2], [ax3, ax4]] = plt.subplots(nrows=2, ncols=2, constrained_layout=True)
fig1, interpol = plt.subplots()
fig2, approx = plt.subplots()
Tc = []
for size in latticeSize:
    t, e, m, cv, x = readFile(filename + size)
    T = np.array(t)
    E = np.array(e)
    M = np.array(m)
    Cv = np.array(cv)
    X = np.array(x)

    # ******************************
    # Energy axis
    ax1.scatter(T, E, label=rf"{size:s}$\times${size:s}")
    ax1.set_ylabel(r"$\langle E \rangle/L^2$")
    ax1.set_xlabel(r"$T$")
    ax1.set_title(r"Mean Energy")
    # ******************************

    # ******************************
    # Magnetization axis
    ax2.scatter(T, M, label=rf"{size:s}$\times${size:s}")
    ax2.set_ylabel(r"$\langle |M| \rangle/L^2$")
    ax2.set_xlabel(r"$T$")
    ax2.set_title(r"Mean Magnetization")
    # ******************************

    # ******************************
    # Heat capacity axis
    ax3.scatter(T, Cv, label=rf"{size:s}$\times${size:s}")
    ax3.set_ylabel(r"$C_v/L^2$")
    ax3.set_xlabel(r"$T$")
    ax3.set_title(r"Heat Capacity")
    # ******************************

    # ******************************
    # Susceptibility axis
    ax4.scatter(T, X, label=rf"{size:s}$\times${size:s}")
    ax4.set_ylabel(r"$\mathcal{X}/L^2$")
    ax4.set_xlabel(r"$T$")
    ax4.set_title(r"Susceptibility")
    # ******************************

    # ******************************
    # interpolation
    Cs = UnivariateSpline(T, Cv, s=5)
    Ts = np.linspace(np.min(T), np.max(T), 100)
    Cv_spline = Cs(Ts)
    interpol.plot(Ts, Cv_spline)
    interpol.scatter(T, Cv, label=rf"{size:s}$\times${size:s}")
    interpol.set_xlabel(r"$T$", size=14)
    interpol.set_ylabel(r"$ C_V/L^2$", size=14)
    interpol.tick_params(labelsize=15)
    interpol.legend(fontsize=12)
    interpol.set_title(r"Interpolation of the heat capacity")
    index = np.where(np.array(Cv_spline) == max(Cv_spline))
    Tc.append(Ts[np.sum(index)])
    # ******************************
# ******************************
# Approximation
inverse_L = [1 / float(i) for i in latticeSize]
approx.scatter(inverse_L, Tc, marker="x", color="r", label="Datapoints")
approx.set_xlabel(r"$1/L$", size=16)
approx.set_ylabel(r"$T_c(L)$", size=16)
approx.tick_params(labelsize=15)
popt, pcov = curve_fit(linear_func, inverse_L, Tc)
X = np.array(inverse_L)
L = np.linspace(35, 130, 1001)
X = [1 / i for i in L]
X = np.array(X)
Y = popt[1] * X + popt[0]
approx.plot(X, Y, "-k")
approx.set_title(r"Interpolation of the maximum values of heat capacity")
equation = r"$T_c(L) = \frac{1.5498}{L} + 2.2665$"
approx.text(0.0110, 2.280, equation, {"color": "k", "fontsize": 14})
approx.legend(fontsize=12)
# ******************************

# ******************************
# Finilization
ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()
plt.show()
# ******************************
