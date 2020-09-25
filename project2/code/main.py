import sys
from os import system
import os
import subprocess
import numpy as np

# ????????????????
# Here goes all autmation of running the program, preferably without comandline arguments, rather use input.
#
# Also remember to make a run.py file if taking commandline arguments when running everything

path_cpp = "./cpp_codes/main"

# Getting input, either from commandline(for automation) or from input, individual running.
if (len(sys.argv) > 5):
    raise Exception("Too many input arguments where given. 6 needed in total.")
elif (len(sys.argv) > 2):
    problem = sys.argv[1]
    n = sys.argv[2]
    plot = sys.argv[3]
    delete = sys.argv[4]

else:
    problem = input("Which problem is solved? [bb/qd1e] ")
    n = input("Number of gridpoints? [int] ")
    plot = input("Do you want to plot the data? [y/n] ")
    delete = input("Do you want to delete the output files? [y/n] ")


# Compiling using makefile
print("Compiling ...")
system("cd cpp_codes/ && make")
print("Compiling done.")
print("Running tests...")
system("cd cpp_codes/ && ./testcode")
print("Testing done.")

# File management
if problem == "bb":
    problem = "BucklingBeam"
    filename_plot = "plot_BB"
    filename_data = "BB"
    path_data = "./BB_data"
    path_data_output = "../cpp_codes/output/"
    path_plot = "./BB_plot"

    a = "&&"
    for i in ([10, 25, 75, 100, 150, 200, 300, 500]):
        system("cd cpp_codes/ " + a + " ./main " + str(i) +
               " 0 " + filename_data + str(i) + " 0 1")

    # Directory management (This is done as long as the programs are ran)
    if not os.path.exists(path_data):
        os.makedirs(path_data)

    if delete == "y":
        system("rm -f " + path_data + "*")


if problem == "qd1e":
    problem = "QD_oneElectron"
    filename_plot = "plot_QD_oneElectron"
    filename_data = "QD_oneElectron"
    path_data = "./QD_data"
    path_plot = "./QD_plot"

    rho_value = input("Do you want one or multiple rho values? [double/multi]")
    if (rho_value == "multi"):
        rho = np.linspace(2, 12, 11)  # 11 points [2,3,4,5,6,7,8,9,10,11,12]

    multi_n = input("Do you want to iterate for multiple values of n? [y/n]")
    if (multi_n == "y" or n == "multi"):
        n = [100, 200, 300, 400]
    else:
        n = [n]

    for rho_max in rho:
        print(rho_max)
        for i in n:
            system(path_cpp + " " + str(i) + " 1 " +
                   filename_data + str(rho_max) + "_" + " 0 " + str(rho_max) + " 5")

    if not os.path.exists(path_data):
        os.makedirs(path_data)

    if delete == "y":
        system("rm -f " + path_data + "*")


# if plot == "y":
#     if not os.path.exists(path_plot):
#         os.makedirs(path_plot)
    # Move files


# an attempt at compiling using make and subprocess but desired output not present.
# output = subprocess.Popen(
#     ["make"], stdout=subprocess.PIPE,  cwd="./cpp_codes")
# stdout = output.communicate()[0]
# print(stdout)
