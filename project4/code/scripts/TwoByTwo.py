import numpy as np
from os import system
import sys

filename = "../cpp/data/2x2/twoXtwo"
dump = "../cpp/data/2x2/Collection"
fileNumbers = [sys.argv[1]]

counter = 0
for number in fileNumbers:
    energyValues = []
    magentizationValues = []
    specificHeatCapacityValues = []
    susceptebilityValues = []
    ee = []
    mm = []
    with open(dump + number, 'r') as f:
        for line in f:
            line = line.split()
            energyValues.append(float(line[0]))
            magentizationValues.append(float(line[1]))
            specificHeatCapacityValues.append(float(line[2]))
            susceptebilityValues.append(float(line[3]))
            ee.append(float(line[4]))
            mm.append(float(line[5]))

            counter += 1
    meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
    meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
    meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
    meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
    ee = np.mean(np.array(ee), dtype=np.float64)
    mm = np.mean(np.array(mm), dtype=np.float64)
    print(r"")
    print(r"##########################################################")
    print(rf"The mean energy for 1e{int(number):d} is: {meanEnergyValues:.6f}")
    print(rf"The mean magnetization for 1e{int(number):d} is: {meanMagnetiziationValues:.6f}")
    print(rf"The mean spesific heat capacity for 1e{int(number):d} is: {meanSpecificHeatCapacityValues:.6f}")
    print(rf"The mean susceptebility for 1e{int(number):d} is: {meanSusceptebilityValues:.6f}")
    print(rf"The mean EE for 1e{int(number):d} is: {ee:.6f}")
    print(rf"The mean MM for 1e{int(number):d} is: {mm:.6f}")
    print(r"##########################################################")
