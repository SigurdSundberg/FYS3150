import numpy as np
from os import system
import sys

filename = "../cpp/data/para/Lattice"
dump = "../cpp/data/para/Collection"
fileNumbers = ["2"]

energyValues = []
magentizationValues = []
specificHeatCapacityValues = []
susceptebilityValues = []
for number in fileNumbers:
    with open(filename + str(number), 'r') as f:
        f.readline()
        for line in f:
            line = line.split()
            energyValues.append(float(line[1]))
            magentizationValues.append(float(line[3]))
            specificHeatCapacityValues.append(float(line[2]))
            susceptebilityValues.append(float(line[4]))

        meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
        meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
        meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
        meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
    with open(dump + number, 'a') as o:
        o.write(" ".join([str(meanEnergyValues), str(meanMagnetiziationValues), str(meanSpecificHeatCapacityValues), str(meanSusceptebilityValues)]) + "\n")

for number in fileNumbers:
    energyValues = []
    magentizationValues = []
    specificHeatCapacityValues = []
    susceptebilityValues = []
    with open(filename + number, 'r') as f:
        for line in f:
            line = line.split()
            energyValues.append(float(line[0]))
            magentizationValues.append(float(line[1]))
            specificHeatCapacityValues.append(float(line[2]))
            susceptebilityValues.append(float(line[3]))

    meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
    meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
    meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
    meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
    print(r"")
    print(r"##########################################################")
    print(rf"The mean energy for 1e{int(number):d} is: {meanEnergyValues:.6f}")
    print(rf"The mean magnetization for 1e{int(number):d} is: {meanMagnetiziationValues:.6f}")
    print(rf"The mean spesific heat capacity for 1e{int(number):d} is: {meanSpecificHeatCapacityValues:.6f}")
    print(rf"The mean susceptebility for 1e{int(number):d} is: {meanSusceptebilityValues:.6f}")
    print(r"##########################################################")
