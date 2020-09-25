import sys
from os import system
import os
import subprocess
import numpy as np


def delete_files(paths, kwargs=0):
    """Deletes files and directory if not files present. 
    If only paths is supplied, then it deletes all files in directory and the directory.
    If kwargs are passed, then it only deletes the respective files in kwargs, and the directory if empty. 

    Args:
        paths (str): path to directory
        kwargs ([str], optional): list of files to be deleted. Defaults to False.
    """
    if not kwargs:
        for _file in os.listdir(paths):
            os.remove(paths + _file)
        if not os.listdir(paths):
            os.rmdir(paths)
    else:
        if not isinstance(kwargs, list):
            kwargs = [kwargs]
        for _file in kwargs:
            os.remove(paths + _file)
        if not os.listdir(paths):
            os.rmdir(paths)


def create_directory(paths):
    if not isinstance(paths, list):
        paths = [paths]
    for directory in paths:
        if not os.path.exists(directory):
            os.mkdir(directory)


path_cpp = "./cpp_codes/main"
path_data_output = "./cpp_codes/output/"
path_scripts = "./scripts/"
path_GEN = "./GEN_data/"


# Compiling using makefile
print("Compiling ...")
system("cd cpp_codes/ && make")
print("Compiling done.")
print("Running tests...")
system("./cpp_codes/testcode")
print("Testing done.")

print("What problem do you want to solve? Default: NONE")
problem = input("[bb, qd1e] ")


if (problem != "bb" and problem != "qd1e"):
    print("No problem given. Exiting...")
    exit(1)

if problem == "bb":
    filename_plot = "plot_BB"
    filename_data = "BB"
    path_data = "./BB_data"
    path_plot = "./BB_plot"

    file_iterations = "time_iterations_"
    file_timecomp = "time_Comparison_BB"

    print("")
    print("BUCKLING BEAM \n")

    # Create directories for output if not already exsisting
    create_directory([path_data, path_plot, path_data_output])

    # Remove files containing iterations if they exsist.
    for string in ["bi_", "ja_"]:
        _files = file_iterations + string + filename_data
        if (os.path.isfile(path_GEN + _files)):
            delete_files(path_GEN, _files)

    print("Enter desired tolerance: Default: 10^(-10)")
    tolerance = input("10^(-[int]) ")
    if (not tolerance.isdigit()):
        tolerance = str(10)
    print(f"Tolerance = 10^(-{tolerance:s})")

    print(
        "Number of meshgrid points? Default: [10, 25, 75, 100, 150, 200, 300, 500]")
    n = input("[int] ")
    if (not n.isdigit()):
        n = [10, 25, 75, 100, 150, 200, 300, 500]
    else:
        n = [n]
    print(f"Running program for n = {n}")
    for i in n:
        print(f"n = {i:d}")
        system(path_cpp + " " + str(i) +
               " 0 " + filename_data + " 0 1 " + tolerance + " 1")
    print("Finished computing...")

    print("Do you want to run a benchmark runtime test? Default: no")
    benchmark = input("[y/n] ")
    if (benchmark == "y"):
        print("Removing benchmark files if they exsist...")
        if (os.path.isfile(path_GEN + file_timecomp)):
            delete_files(path_GEN, file_timecomp)
        m = [10, 25, 75, 100, 150, 200, 300, 500]
        print("This will take a while, make sure the laptop has power and that no other large program is running for an accurate measurement.")
        print("We will run over n = [10, 25, 75, 100, 150, 200, 300, 500]")
        print("Do you want to add more numbers?")
        while True:
            add = input("[int] ")
            if (add == "" or add == "n"):
                break
            if (add.isdigit()):
                m.append(int(add))
            else:
                print(
                    f"{add:s} is not an integer. Enter [int] or press enter or n + enter to continue the program.")
        print("We do this k times. Default for k is 20.")
        k = input("[int] ")
        if (not k.isdigit()):
            k = 20
        else:
            k = int(k)
        for j in range(k):
            for i in m:
                system(path_cpp + " " + str(i) +
                       " 0 " + filename_data + " 0 1 " + tolerance + " 2")

        print("Do you want to plot the time comparison? Default: no")
        plot_timecomp = input("[y/n] ")
        if (plot_timecomp == "y"):
            system("python3 " + path_scripts +
                   "plot_timecomp.py " + filename_data)
    else:
        print("Do you already have a benchmark you want to plot? Default: n")
        plot_timecomp = input("[y/n] ")
        if (plot_timecomp == "y"):
            system("python3 " + path_scripts +
                   "plot_timecomp.py " + filename_data)

    print("Do you want to create a iterations plot? Default: no")
    plot_iterations = input("[y/n] ")
    if (plot_iterations == "y"):
        system("python3 " + path_scripts +
               "plot_iterations_n.py " + filename_data)

    print("Do you want to plot the eigenvectors? Default: no")
    plot_eigenvector = input("[y/n] ")
    if (plot_eigenvector == "y"):
        print("Largest index of eigenvalue you want to plot? Default: 3")
        largest_eigenvalue = input("[int] ")
        if (not largest_eigenvalue.isdigit()):
            largest_eigenvalue = "3"
        print("Number of gridpoints wanted to plot for? Default: 200")
        n = input("[int] ")
        if (not n.isdigit()):
            n = "200"
        if (not os.path.isfile(path_data_output + "data_" + filename_data + n)):
            print(f"Creating data file for n = {n}")
            system(path_cpp + " " + n +
                   " 0 " + filename_data + " 0 1 " + tolerance + " 1")
            print("Plotting...")
        system("python3 " + path_scripts + "plot_eigenvector.py " +
               filename_data + " " + n + " " + largest_eigenvalue)

    print("Do you want to delete the output files? Default: yes")
    delete = input("[y/n] ")

    if (delete == "y"):
        # Asking if all files should be deleted or only spesific
        files = []
        print("Specify which files, if NONE all are deleted: Default: NONE")
        while True:
            specific = input("[str] ")
            if (specific == "" or specific == "NONE"):
                break
            files.append(specific)
        if (not files):
            delete_files(path_data_output)
        else:
            delete_files(path_data_output, files)
    elif(delete != "n"):
        print("You sure you want to delete the files? Default: yes")
        delete = input("[y/n]  ")
        if (delete != "n"):
            delete_files(path_data_output)

    print("Do you want to delete general files? Default: no")
    print("These files are in the folder GEN_data, and are the files containing time comparison and iterations.")
    delete = input("[y/n] ")
    if (delete == "y"):
        delete_files(path_GEN)

    print("Thank you... Have a nice day.")


if problem == "qd1e":
    filename_plot = "plot_QD_oneElectron"
    filename_data = "QD_oneElectron"
    path_data = "./QD_data"
    path_plot = "./QD_plot"

    print("QUANTUM DOTS ONE ELECTRON \n")

    # Create directories for output if not already exsisting
    create_directory([path_data, path_plot, path_data_output])

    print("Enter desired tolerance: Default: 10^(-10)")
    tolerance = input("10^(-[int]) ")
    if (not tolerance.isdigit()):
        tolerance = 10

    rho_value = input("Do you want one or multiple rho values? [double/multi]")
    if (rho_value == "multi"):
        rho = np.linspace(2, 12, 11)  # 11 points [2,3,4,5,6,7,8,9,10,11,12]

    multi_n = input("Do you want to iterate for multiple values of n? [y/n] ")
    if (multi_n == "y" or n == "multi"):
        n = [100, 200, 300, 400]

    for rho_max in rho:
        print(rho_max)
        for i in n:
            system(path_cpp + " " + str(i) + " 1 " +
                   filename_data + str(rho_max) + "_" + " 0 " + str(rho_max) + " 5")

    if delete == "y":
        delete_files(path_data_output)
