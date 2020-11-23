import numpy as np
from os import system
import sys


# def meanValues(inputFile):
#     energyValues = []
#     magentizationValues = []
#     specificHeatCapacityValues = []
#     susceptebilityValues = []
#     with open(inputFile, 'r') as f:
#         suffix = f.readline()
#         for line in f:
#             line = line.split()
#             energyValues.append(float(line[1]))
#             magentizationValues.append(float(line[2]))
#             specificHeatCapacityValues.append(float(line[3]))
#             susceptebilityValues.append(float(line[4]))
#     meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
#     meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
#     meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
#     meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
#     return (suffix, meanEnergyValues, meanMagnetiziationValues, meanSpecificHeatCapacityValues, meanSusceptebilityValues)


# def readFileForPrinting(inputFile):
#     energyValues = []
#     magentizationValues = []
#     specificHeatCapacityValues = []
#     susceptebilityValues = []
#     with open(inputFile, 'r') as f:
#         for line in f:
#             line = line.split()
#             energyValues.append(float(line[0]))
#             magentizationValues.append(float(line[1]))
#             specificHeatCapacityValues.append(float(line[2]))
#             susceptebilityValues.append(float(line[3]))
#     meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
#     meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
#     meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
#     meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
#     return (meanEnergyValues, meanMagnetiziationValues, meanSpecificHeatCapacityValues, meanSusceptebilityValues)


# def consolidateFiles(inputFile, outputFile):
#     with open(outputFile + "_" + kwargs[0], 'a') as o:
#         o.write(" ".join([kwargs[1], kwargs[2], kwargs[3], kwargs[4]]) + "\n")


def stringToList(inputList):
    res = inputList.strip().split()
    for i, ele in enumerate(res):
        res[i] = float(ele)
    return res


def readFile(inputFile):
    with open(inputFile, 'r') as f:
        firstLine = int(f.readline())
        return (firstLine, stringToList(f.readline())[1::])


def printing(args, outputFile):
    with open(outputFile, 'a') as o:
        o.write(r"##########################################################" + "\n")
        o.write(rf"Number of Montecarlo Cycles: {args[0]:d}" + "\n")
        o.write(rf"Mean Energy:                 {args[1][0]:.6f}" + "\n")
        o.write(rf"Mean Magnetization:          {args[1][4]:.6f}" + "\n")
        o.write(rf"Mean Spesific Heat Capacity: {args[1][1]:.6f}" + "\n")
        o.write(rf"Mean Susceptebility:         {args[1][3]:.6f}" + "\n")
        o.write(r"##########################################################" + "\n")


inputFile = sys.argv[1]
outputFile = sys.argv[2]
args = readFile(inputFile)
printing(args, outputFile)
system("rm " + inputFile)

# for number in fileNumbers:
#     MCs = 10**(int(number))
#     system("./cpp/main " + number + " " + str(MCs))
#     energyValues = []
#     magentizationValues = []
#     specificHeatCapacityValues = []
#     susceptebilityValues = []

#     with open(filename + str(number), 'r') as f:
#         f.readline()
#         for line in f:
#             line = line.split()
#             energyValues.append(float(line[1]))
#             magentizationValues.append(float(line[3]))
#             specificHeatCapacityValues.append(float(line[2]))
#             susceptebilityValues.append(float(line[4]))

#         meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
#         meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
#         meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
#         meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
#     with open(dump + number, 'a') as o:
#         o.write(" ".join([str(meanEnergyValues), str(meanMagnetiziationValues), str(meanSpecificHeatCapacityValues), str(meanSusceptebilityValues)]) + "\n")
#     system("rm ./cpp/data/2x2/twoXtwo" + number)


# for number in fileNumbers:
#     energyValues = []
#     magentizationValues = []
#     specificHeatCapacityValues = []
#     susceptebilityValues = []
#     with open(dump + number, 'r') as f:
#         for line in f:
#             line = line.split()
#             energyValues.append(float(line[0]))
#             magentizationValues.append(float(line[1]))
#             specificHeatCapacityValues.append(float(line[2]))
#             susceptebilityValues.append(float(line[3]))

#     meanEnergyValues = np.mean(np.array(energyValues), dtype=np.float64)
#     meanMagnetiziationValues = np.mean(np.array(magentizationValues), dtype=np.float64)
#     meanSpecificHeatCapacityValues = np.mean(np.array(specificHeatCapacityValues), dtype=np.float64)
#     meanSusceptebilityValues = np.mean(np.array(susceptebilityValues), dtype=np.float64)
