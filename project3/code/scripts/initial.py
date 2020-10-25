import numpy as np
x = []
y = []
z = []
vx = []
vy = []
vz = []

# Velocity is in Au /d not Au/yr
DtY = (365.24)
with open("initBary.txt", 'r') as f:
    f.readline()
    while True:
        R = f.readline().strip("\n").rstrip().split(" ")
        V = f.readline().strip("\n").rstrip().split(" ")
        if (len(R) != 6):
            break
        x.append(R[1])
        y.append(R[3])
        z.append(R[5])
        vx.append(str(float(V[1])*DtY))
        vy.append(str(float(V[3])*DtY))
        vz.append(str(float(V[5])*DtY))

with open("../classes/Input/initialBary.txt", 'w') as o:
    for i in range(len(x)):
        o.write(
            f"{x[i]:25s} {y[i]:25s} {z[i]:25s} {vx[i]:25s} {vy[i]:25s} {vz[i]:25s} \n")
