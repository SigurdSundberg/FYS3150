"""
From the animation plot we can see that
time=0.1 gives a smooth curve
time=0.35 gives a almost linear(steady state) curve
"""
import matplotlib.pyplot as plt
import numpy as np
import scipy.integrate as integrate

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]}
)

path = "../cpp/data/1D/"
s = "001"
suffix = s + "FINAL"
files = ["FE", "BE", "CN"]
timeValues = [0.1, 0.4]
tstrings = ["01", "04"]


def f(x):
    """Takes x values in the range of xmin to xmax with step length dx

    Args:
        x (array-like/float): xvalues to be calculated

    Returns:
        array-like/float: the returned x values
    """
    return -x


def readFile(filename, timePoint):
    x = []
    y = []
    tmp = []
    with open(filename, 'r') as o:
        for line in o:
            if (line[0] == "t"):
                x.append(timePoint)
                dataPoints = int(o.readline().split("=")[1])
                xArray = np.linspace(0, 1, dataPoints)
                F = f(xArray)
                for _ in range(dataPoints):
                    tmp.append(float(o.readline()))
                y.append(tmp)
                tmp = []
            if (len(x) == len(timePoint)):
                for i in range(len(y)):
                    y[i][:] = y[i][:] - F
                return (x, np.array(y), dataPoints)


def analytical(t, xArr=""):
    if isinstance(xArr, str):
        analyticalGrid = np.linspace(0, 1, 101)
    else:
        analyticalGrid = xArr
    F = f(analyticalGrid)
    analyticalSolution = 0
    currentIteration = float('inf')
    fourierCoefficient = 1

    i = 1
    while np.max(np.abs(currentIteration) > 1e-14):
        fourierCoefficient = 2 * (np.pi * i * np.cos(np.pi * i) - np.sin(np.pi * i)) / (i * i * np.pi * np.pi)
        currentIteration = fourierCoefficient * np.sin(i * np.pi * analyticalGrid) * np.exp(-i * i * np.pi * np.pi * t)
        analyticalSolution += currentIteration
        i += 1

    analyticalSolution = analyticalSolution - F
    return analyticalGrid, analyticalSolution


def error(B, x, t):
    _, A = analytical(t, x)
    return A - B


x_data, FE, n = readFile(path + files[0] + suffix, timeValues)
_, BE, _ = readFile(path + files[1] + suffix, timeValues)
_, CN, _ = readFile(path + files[2] + suffix, timeValues)
xArray = np.linspace(0, 1, n)


for i in range(len(x_data)):
    fig, ax = plt.subplots()

    ax.set_xlim(0, 1)
    ax.set_ylim(-0.001, 1.1)

    ax.set_xlabel(r"x-position")
    ax.set_ylabel(r"Temperature")
    ax.set_title(rf"1D solutions, t = {timeValues[i]:.3f}")
    Ax, Ay = analytical(timeValues[i])
    ax.plot(Ax, Ay, "k", label=r"Analytical Solution")
    ax.plot(xArray, FE[i][:], "--", label=r"Forward Euler")
    ax.plot(xArray, BE[i][:], "-.", label=r"Backward Euler")
    ax.plot(xArray, CN[i][:], "g:", label=r"Crank Nicholson")
    plt.legend()
    plt.savefig(r"../../report/figures/plot1d" + f"{tstrings[i]}" + s)
    plt.show()

    fig, ax = plt.subplots()

    ax.set_xlabel(r"x-position")
    ax.set_ylabel(r"Absolute Difference")
    ax.set_title(rf"Error, t = {timeValues[i]:.3f}")

    ax.plot(xArray, error(FE[i][:], xArray, timeValues[i]), "--", label=r"Forward Euler")
    ax.plot(xArray, error(BE[i][:], xArray, timeValues[i]), "-.", label=r"Backward Euler")
    ax.plot(xArray, error(CN[i][:], xArray, timeValues[i]), "g:", label=r"Crank Nicholson")
    plt.legend()
    plt.savefig(r"../../report/figures/error" + f"{tstrings[i]}" + s)
    plt.show()
