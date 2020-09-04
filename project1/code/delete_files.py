from os import system
import sys
import os.path

try:
    algo = sys.argv[1]
    n = int(sys.argv[2])
except:
    print("Problem in " + sys.argv[0] + f" with input {algo} or {n}")

# Deleting files
for i in range(1, n+1):
    system("rm ./output/timed_" + algo + str(i))
    if not os.path.isfile("./output/" + algo + str(i)):
        continue
    else:
        system("rm ./output/" + algo + str(i))
