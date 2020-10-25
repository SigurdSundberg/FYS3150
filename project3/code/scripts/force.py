import numpy as np
import matplotlib.pyplot as plt

n = 6
# files = ['Plot0Elip.xyz', 'Plot1Elip.xyz', 'Plot2Elip.xyz',
#          'Plot3Elip.xyz', 'Plot4Elip.xyz', 'Plot5Elip.xyz']
# path = "../classes/Data/AlphaElip/"
# files = ['Plot0Circ.xyz', 'Plot1Circ.xyz', 'Plot2Circ.xyz',
#          'Plot3Circ.xyz', 'Plot4Circ.xyz', 'Plot5Circ.xyz']
# path = "../classes/Data/AlphaCirc/"

Y = []

for _ in range(n):
    Y.append([])

i = 0
for filename in files:
    with open(path + filename, 'r') as f:
        for line in f:
            line = line.split()
            Y[i].append(float(line[1]))
    i += 1


N = int(300/0.01)
t = np.linspace(0.01, 300, N)
dt = [2.96, 2.98, 3, 3.02, 3.04, 3.06]

f, (ax1, ax2) = plt.subplots(1, 2, sharey=True)


for i in range(n):
    ax1.plot(t, Y[i], label=rf"$\alpha$: {dt[i]}")
    ax2.plot(t, Y[i], label=rf"$\alpha$: {dt[i]}")

# zoom-in / limit the view to different portions of the data
ax2.set_xlim(50, 300)  # outliers only
ax1.set_xlim(0, 15)  # most of the data
ax1.set_ylim(0, 10)

# hide the spines between ax and ax2
ax1.spines['right'].set_visible(False)
ax2.spines['left'].set_visible(False)
ax1.yaxis.tick_left()
ax1.tick_params(labeltop=False)  # don't put tick labels at the top
ax2.yaxis.tick_right()

# Now, let's turn towards the cut-out slanted lines.
# We create line objects in axes coordinates, in which (0,0), (0,1),
# (1,0), and (1,1) are the four corners of the axes.
# The slanted lines themselves are markers at those locations, such that the
# lines keep their angle and position, independent of the axes size or scale
# Finally, we need to disable clipping.

d = .5  # proportion of vertical to horizontal extent of the slanted line
kwargs = dict(marker=[(-1, -d), (1, d)], markersize=12,
              linestyle="none", color='k', mec='k', mew=1, clip_on=False)
ax1.plot([1, 1], [0, 1], transform=ax1.transAxes, **kwargs)
ax2.plot([0, 0], [0, 1], transform=ax2.transAxes, **kwargs)


ax1.set_ylabel(" Distance to the Sun: [AU]")
ax1.set_xlabel(" Time in years")
ax2.set_xlabel(" Time in years")
f.suptitle(r" Initial velocity $2\pi$AU/year, different force")
plt.legend()
plt.show()
