from os import system
import time
print("This program has done its job. Do not run again unless you need another timing.")
# Run over 8 different temperatures [1, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 4]
# We want to run over different lattice size [20, 40, 60, 80, 100]
# For 100000 MonteCarlo cycles in total.
# >>> Non Paralell run we have 100000 cycles
# >>> Paralell run we have 12500 cycles

filename = "./data/time/Timing"
dimList = [20, 40, 60, 80, 100]
MCs = 100000
orderList = [1]
tInitialList = [1]
tFinal = 3
tStep = 0.5
compilerFlagList = ["", "-O2", "-O3", "-Ofast"]
# ********************************
# Non Paralell
program = "./main"
filename += "Normal"
for compilerFlag in compilerFlagList:
    compileCommandPrefix = "c++"
    compileCommandSuffix = "-c main.cpp"
    compileCommandFinalPrefix = "c++"
    compileCommandFinalSuffix = "main.o lib.o -o main"
    compilerCommandCompile = " ".join([compileCommandPrefix, compilerFlag, compileCommandSuffix])
    print(compilerCommandCompile)
    system(compilerCommandCompile)
    time.sleep(1)
    compilerCommandCompileFinal = " ".join([compileCommandFinalPrefix, compilerFlag, compileCommandFinalSuffix])
    system(compilerCommandCompileFinal)
    print(compilerCommandCompileFinal)
    for _ in range(3):
        for dim in dimList:
            for tInitial in tInitialList:
                for order in orderList:
                    fileName = filename + "_" + compilerFlag + "_"
                    command = " ".join([program, fileName, str(dim),
                                        str(MCs), str(order), str(tInitial), str(tFinal), str(tStep)])
                    print(command)
                    # Run part
                    system(command)

input("Done with the Normal calculations")
# ********************************
filename = "./data/time/Timing"

# ********************************
# Parallel
filename += "Para"
program = "./paraIsing"
processors = "8"
string = "mpirun -np"
MCs = int(MCs / 8)
for compilerFlag in compilerFlagList:
    compileCommandPrefix = "mpic++"
    compileCommandSuffix = "-c paraIsing.cpp"
    compileCommandFinalPrefix = "mpic++"
    compileCommandFinalSuffix = "paraIsing.o lib.o -o paraIsing"
    compilerCommandCompile = " ".join([compileCommandPrefix, compilerFlag, compileCommandSuffix])
    print(compilerCommandCompile)
    system(compilerCommandCompile)
    time.sleep(1)
    compilerCommandCompileFinal = " ".join([compileCommandFinalPrefix, compilerFlag, compileCommandFinalSuffix])
    system(compilerCommandCompileFinal)
    print(compilerCommandCompileFinal)
    for _ in range(3):
        for dim in dimList:
            for tInitial in tInitialList:
                for order in orderList:
                    fileName = filename + "_" + str(tInitial) + "_"
                    command = " ".join([string, processors, program, fileName, str(dim),
                                        str(MCs), str(order), str(tInitial), str(tFinal), str(tStep)])
                    print(command)
                    # Run part
                    system(command)
# ********************************
