import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
plt.rcParams.update({
    "text.usetex": True,
    "font.sans-serif": ["Helvetica"],
    "font.family": "DejaVu Sans"})

# filename = "../classes/Data/V2.xyz"
# filename = "../classes/Data/V3.xyz"
filename = "../classes/Data/V10.xyz"

with open(filename, 'r') as f:
    N = int(f.readline())
    string = f.readline()
    X = []
    Y = []
    Z = []
    for _ in range(N):
        X.append([])
        Y.append([])
        Z.append([])
    for line in f:
        line = line.split()
        Id = int(line[0])
        X[Id - 1].append(float(line[1]))
        Y[Id - 1].append(float(line[2]))
        Z[Id - 1].append(float(line[3]))

planets = ["Sun", "Earth", "Jupiter", "Mars", "Venus",
           "Saturn", "Mercury", "Uranus", "Neptun", "Pluto"]
for i in range(N):
    ax.plot(X[i][:], Y[i][:], Z[i][:], label=f"{planets[i]:s}")
ax.set_xlabel("x-position [AU]")
ax.set_ylabel("y-position [AU]")
ax.set_zlabel("z-position [AU]")
plt.legend()
plt.show()

# Plotting inner planets
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
innerplanets = ["Sun", "Earth", "Mars", "Venus", "Mercury"]
n = len(X[0][:])
for i in range(N):
    if (planets[i] in innerplanets):
        print(planets[i])
        ax.plot(X[i][:int(n/100)], Y[i][:int(n/100)], Z[i]
                [:int(n/100)], label=f"{planets[i]:s}")
ax.set_xlabel("x-position [AU]")
ax.set_ylabel("y-position [AU]")
ax.set_zlabel("z-position [AU]")
plt.legend()
plt.show()

""" 
# This is the dumb way of doing this, method above works way better
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

filename = "../classes/V3.xyz"
with open(filename, 'r') as f:
    n = int(f.readline())
    string = f.readline()
    p1 = []
    p2 = []
    p3 = []
    for line in f:
        line = line.split()
        Id = int(line[0])
        if Id == 1:
            p1.append((float(line[1]), float(line[2]), float(line[3])))
        if Id == 2:
            p2.append((float(line[1]), float(line[2]), float(line[3])))
        if Id == 3:
            p3.append((float(line[1]), float(line[2]), float(line[3])))
n = len(p1)

p1x = np.zeros(n)
p1y = np.zeros(n)
p1z = np.zeros(n)
p2x = np.zeros(n)
p2y = np.zeros(n)
p2z = np.zeros(n)
p3x = np.zeros(n)
p3y = np.zeros(n)
p3z = np.zeros(n)

for i in range(n):
    p1x[i] = p1[i][0]
    p1y[i] = p1[i][1]
    p1z[i] = p1[i][2]
    p2x[i] = p2[i][0]
    p2y[i] = p2[i][1]
    p2z[i] = p2[i][2]
    p3x[i] = p3[i][0]
    p3y[i] = p3[i][1]
    p3z[i] = p3[i][2]

ax.plot(p1x, p1y, p1z)
ax.plot(p2x, p2y, p2z)
ax.plot(p3x, p3y, p3z)
plt.show()
"""
