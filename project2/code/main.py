import sys
import os


"""
Here goes all autmation of running the program, preferably without comandline arguments, rather use input. 

Also remember to make a run.py file if taking commandline arguments when running everything
"""

# Getting input, either from commandline(for automation) or from input, individual running.
if len(sys.argv > 8):
    raise Exception("Too few input arguments where given. 6 needed in total.")
elif len(sys.argv > 1):
    problem = sys.argv[1]
    comp = sys.argv[2]
    test = sys.argv[3]
    n = sys.argv[4]
    max_it = sys.argv[5]
    plot = sys.argv[6]
    delete = sys.argv[7]

else:
    problem = input("Which problem is solved? [bb/qd1m]")
    comp = input("Do you want to compile the files? [y/n]")
    n = input("Number of gridpoints? [10^n]")
    max_it = input("Max number of iterations? [int/d]")  # d = n * n * n
    plot = input("Do you want to plot the data? [y/n]")
    delete = input("Do you want to delete the output files? [y/n]")
    test = input("Do you want to run unit tests? [y/n]")


# File management
if problem == "bb":
    problem = "BucklingBeam"
    filename_plot = ""
    filename_data = ""
    path_data = ""
    path_plot = ""
if problem == "qd1m":
    problem = "QD_oneElectron"
    filename_plot = ""
    filename_data = ""
    path_data = ""
    path_plot = ""


# Compiler
if comp == "y":
    a = -1
    # Call makefile, with compiler for cpp

if test == "y":
    a = -1
    # call makefile for test.cpp and run the tests to see if programs do as expected

# Directory management (This is done aslong as the programs are ran)
if not os.path.exists(path_data):
    os.makedirs(path_data)
# Move files and handle them

if plot == "y":
    if not os.path.exists(path_plot):
        os.makedirs(path_plot)
    # Move files

if delete == "y":
    a = -1
    # Delete files
