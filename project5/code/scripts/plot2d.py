import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]}
)

path = "../cpp/data/2D/"
suffix = "001"
files = ["2D"]
final = "FINAL"
initialFunction = ["INITIAL2D"]

filename = "../cpp/data/2D/2D0015FINAL"


def function(x):
    """Takes x values in the range of xmin to xmax with step length dx

    Args:
        x (array-like/float): xvalues to be calculated

    Returns:
        array-like/float: the returned x values
    """
    return -x


def f2(x, y): return -x


def analytical1d(x, t):
    F = function(x)
    analyticalSolution = 0
    currentIteration = float('inf')
    fourierCoefficient = 1

    i = 1
    while (np.max(np.abs(currentIteration)) > 1e-16):
        fourierCoefficient = 2 * (np.pi * i * np.cos(np.pi * i) - np.sin(np.pi * i)) / (i * i * np.pi * np.pi)
        currentIteration = fourierCoefficient * np.sin(i * np.pi * x) * np.exp(-i * i * np.pi * np.pi * t)
        analyticalSolution += currentIteration
        i += 1

    analyticalSolution = analyticalSolution
    return analyticalSolution


# def analytical2d(x, y, t):
#     F = f2(x, y)

#     def A(i):
#         p = np.pi
#         return (4 * (i * p * np.cos(i * p) - np.sin(i * p)) * np.sin(i * p)) / (i**3 * p**3)

#     def lmn(i, j): return np.pi**2 * (i**2 + j**2) / (1**2)

#     def func(x, y, i, j, t):
#         return np.sin(i * np.pi * x) * np.cos(j * np.pi * y) * np.exp(-lmn(i, j) * t)
#     k = 1
#     aS = 0
#     cI = float('-inf')

#     while (np.max(np.abs(cI)) > 1e-14):
#         cI = A(k) * func(x, y, i, i, t)
#         aS += cI
#         k += 1
#         print(np.max(np.abs(cI)))
#     print(k)
#     return aS - F

def analytical2d(x, y, t):
    F = f2(x, y)

    m = n = 20

    def A(i):
        p = np.pi
        return 4 * (i * p * np.cos(i * p) - np.sin(i * p)) * np.sin(i * p) / (i**3 * p**3)

    def lmn(i, j): return np.pi**2 * (i**2 + j**2)

    def func(x, y, i, j, t):
        return A(i) * np.sin(i * np.pi * x) * np.cos(j * np.pi * y) * np.exp(-lmn(i, j) * t) * np.exp(-lmn(i, j) * t)

    k = len(x)
    cx = 0
    tmp = np.zeros(m * n)
    sol = np.zeros([k, k])
    for ix in x:
        cy = 0
        for iy in y:
            c = 0
            for i in range(1, n):
                for j in range(1, m):
                    tmp[c] = func(ix, iy, i, j, t)
                    c += 1
            sol[cx, cy] = sum(tmp)
            cy += 1
        cx += 1
    return sol


data = np.loadtxt(filename, dtype=float, skiprows=2)
with open(filename, 'r') as f:
    t = float(f.readline().split("=")[1])

# We need to manip data with the inital function
n = len(data[0])
x = np.linspace(0, 1, n)
F = function(x)
for i in range(n):
    data[:, i] -= F
X, Y = np.meshgrid(x, x)

fig, ax = plt.subplots()
ax.imshow(data.transpose(), cmap='Greys', extent=[0, 1, 1, 0])
ax.set_title(rf"2D diffusion, time = {t:.2f}")
ax.set_xlabel(r"x")
ax.set_ylabel(r"y")
ax.xaxis.set_ticks_position('top')
ax.xaxis.set_label_position('top')
plt.show()


# fig, ax = plt.subplots()
# ax.imshow(data, cmap='Greys', extent=[0, 1, 1, 0])
# ax.set_title(rf"1D Expanded, t = 0.1")
# ax.set_xlabel(r"x")
# ax.set_ylabel(r"y")
# ax.xaxis.set_ticks_position('top')
# ax.xaxis.set_label_position('top')
# ana = analytical1d(x, 0.1)
# sol = np.zeros([n, n])
# for i in range(n):
#     sol[i] = ana
# ax.imshow(sol, cmap='Greys', extent=[0, 1, 1, 0])
# plt.show()


# fig, ax = plt.subplots()
# ax.imshow(data, cmap='Greys', extent=[0, 1, 1, 0])
# ax.set_title(rf"2D Analytical, time = 0.1")
# ax.set_xlabel(r"x")
# ax.set_ylabel(r"y")
# ax.xaxis.set_ticks_position('top')
# ax.xaxis.set_label_position('top')

# A2 = analytical2d(x, x, 1)
# ax.imshow(A2, cmap='Greys', extent=[0, 1, 1, 0])
# plt.show()
