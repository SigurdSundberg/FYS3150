from os import system

fileName = "./cpp/data/para/Lattice"
dim = "2"
MCs = "100"
order = "0"
tInitial = "1"
tFinal = "1"
tStep = "1"

program = "./cpp/paraIsing"
processors = "8"
string = "mpirun -np"

numbers = [2, 3, 4, 5, 6]
for number in numbers:
    MCs = str(10**number)

    command = " ".join([string, processors, program, fileName, dim,
                        MCs, order, tInitial, tFinal, tStep])
    print(command)
    input()
    # Run part
    system(command)

    outputFile = "./cpp/data/para/table1"
    output = "python3 ./scripts/dataMerging.py " + fileName + dim + "_" + MCs + " " + outputFile
    system(output)
