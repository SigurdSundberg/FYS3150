import numpy as np
import os


part = str(input("Which part of the project would you run? [b, c, e] \n"))


if part == "e":
    os.system("mpicxx -O2 -c testPara.cpp")
    os.system("mpicxx -O2 -o testPara.exe testPara.o")

else:
    print("compiling")
    os.system("c++ -O3 -Wall -c test.cpp")
    os.system("c++ -O3 -Wall -o test.exe test.o")


if part == "b":
    spin_matrix = str(input("Would you like an ordered or random initial spin matrix? [o/r] \n"))
    if spin_matrix == "o":
        outfilename = "Expectation_values_n_2_ordered.txt"
        outfilename2 = "Relative_error_n_2_ordered.txt"
        initialize_spin_matrix = "ordered"
    elif spin_matrix == "r":
        outfilename = "Expectation_values_n_2_random.txt"
        outfilename2 = "Relative_error_n_2_random.txt"
        initialize_spin_matrix = "random"
    else:
        print("Please choose either o or r, try again")
        os._exit(1)

    number_of_temperatures = "1"
    dimension = "2"
    MC_samples = int(input("Specify number of Monte Carlo samples: "))
    temperature = "1"

    command_line_args = number_of_temperatures + " " + outfilename + " " + dimension \
        + " " + str(MC_samples) + " " + initialize_spin_matrix + " " + temperature + " " + outfilename2
    print("executing")
    os.system("./test.exe" + " " + command_line_args)

    path = "results/2x2"
    if not os.path.exists(path):
        os.makedirs(path)
    os.system("mv" + " " + outfilename + " " + outfilename2 + " " + path)

if part == "c":
    number_of_temperatures = "1"
    dimension = "20"
    MC_samples = int(input("Specify number of Monte Carlo samples: "))
    initialize_spin_matrix = str(input("Ordered or randomized inital spin matrix? [o/r] \n"))
    temperature = float(input("Give temperature: [1.0 or 2.4] \n"))

    if initialize_spin_matrix == "o":
        initialize = "ordered"

    if initialize_spin_matrix == "r":
        initialize = "random"

    outfilename = "MC_" + str(MC_samples) + "_n_" + dimension + "_T_" + str(temperature) + "_" + initialize + "_.txt"
    outfilename2 = "boltzmann_distribution_MC_" + str(MC_samples) + "_T_" + str(temperature) + "_" + initialize + "_.txt"

    command_line_args = number_of_temperatures + " " + outfilename + " " + dimension \
        + " " + str(MC_samples) + " " + initialize + " " + str(temperature) + " " + outfilename2
    print("executing")
    os.system("./test.exe" + " " + command_line_args)

    print("moving files")
    path = "results/partC"
    if not os.path.exists(path):
        os.makedirs(path)
    os.system("mv" + " " + outfilename + " " + outfilename2 + " " + path)
    print("Finito!!!!")

if part == "e":
    time = 250  # Burn-in period as measured in MC_cycles/spins.
    p = 7  # Number of processes.
    total_time = 2 * time
    path = "results/partE/total_time_" + str(total_time) + "burn_in_time_" + str(time) + "/"
    if not os.path.exists(path):
        os.makedirs(path)

    Lattice_sizes = [2]  # [40, 60, 80, 100]
    for L in Lattice_sizes:
        n_spins = L * L
        print("Executing for L = " + str(L))
        MC_samples = int(total_time * n_spins)  # Total number of Monte Carlo cycles
        print("Monte carlo samples = ", MC_samples)
        N = int(time * n_spins)  # Burn-in period.
        arguments = str(L) + " " + str(MC_samples) + " " + str(N)
        os.system("mpirun -np" + " " + str(p) + " " + " ./testPara.exe" + " " + arguments)  # --oversubscribe
        filename = "observables_L_" + str(L) + ".txt"
        os.system("mv" + " " + filename + " " + path)
