"""
File structure is on the form  
time=1
datapoints=11
#### 1
#### 2
#### 3 
#### 4
#### 5 
#### 6 
#### 7
#### 8 
#### 9 
#### 10
#### 11
"""
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np

plt.style.use("bmh")
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "DejaVu Sans",
    "font.sans-serif": ["Helvetica"]}
)

path = "../cpp/data/"
suffix = "01"
files = ["FE", "BE", "CN"]
initialFunction = ["INITIAL"]


def f(x):
    """Takes x values in the range of xmin to xmax with step length dx 

    Args:
        x (array-like/float): xvalues to be calculated

    Returns:
        array-like/float: the returned x values
    """
    return -x


def readFile(filename):
    print(filename)
    x = []
    y = []
    temp = []
    with open(filename, 'r') as f:
        for line in f:
            if line[0] == "t":
                x.append(float(line.split("=")[1]))
            elif line[0] == "d":
                if len(temp) == 11:
                    y.append(temp)
                    temp = []
            else:
                temp.append(float(line))

    return np.array(x), np.array(y)


x_data, y_data = readFile(path + files[0] + suffix)
_, intial = readFile(path + initialFunction[0] + suffix)

fig, ax = plt.subplots()
ax.set_xlim(0, 1)
ax.set_ylim(0, 1.1)
xArray = np.linspace(0, 1, 11)
F = f(xArray)
print(len(y_data))
for i in range(len(y_data)):
    y_data[i][:] = y_data[i][:] - F

line, = ax.plot([], [])

time_text = ax.text(0.1, 0.75, "", transform=ax.transAxes)


def animation_frame(i):
    xArray = np.linspace(0, 1, 11)
    y = y_data[i][:]
    line.set_xdata(xArray)
    line.set_ydata(y)
    if i % 10 == 0:
        time_text.set_text(f"t={x_data[i]:.3f}")
    return tuple([line]) + tuple([time_text])


def init():
    xArray = np.linspace(0, 1, 11)

    line.set_data([xArray], [intial])
    return line,


animation = FuncAnimation(fig, animation_frame, frames=999, interval=20, init_func=init, blit=False)
plt.show()
