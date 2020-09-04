from os import system
import sys

try:
    algo = sys.argv[1]
    n = int(sys.argv[2])
except:
    print("Problem in " + sys.argv[0] + f" with input {algo} or {n}")

# Deleting files
for i in range(1, n+1):
    system("rm ./output/" + algo + str(i))
    system("rm ./output/timed_" + algo + str(i))
