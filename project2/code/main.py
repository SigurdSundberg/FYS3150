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
            if (os.path.isfile(paths + _file)):
                os.remove(paths + _file)
        if not os.listdir(paths):
            os.rmdir(paths)


def create_directory(paths):
    """Creates a directory if it doesn't exist

    Args:
        paths ([str]): either a single string or a list of strings, indicating the paths to the directory in questions 
    """
    if not isinstance(paths, list):
        paths = [paths]
    for directory in paths:
        if not os.path.exists(directory):
            os.mkdir(directory)


def isfloat(value):
    try:
        float(value)
        return True
    except ValueError:
        return False


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
    create_directory([path_data, path_plot, path_data_output, path_GEN])

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
        print(f"n = {m}")
        print("We do this k times. Default for k is 20.")
        k = input("[int] ")
        if (not k.isdigit()):
            k = 20
        else:
            k = int(k)
        for j in range(k):
            print(f"Running for k = {j+1:d}")
            for i in m:
                system(path_cpp + " " + str(i) +
                       " 0 " + filename_data + " 0 1 " + tolerance + " 2")

        print("Do you want to plot the time comparison? Default: no")
        plot_timecomp = input("[y/n] ")
        if (plot_timecomp == "y"):
            system("python3 " + path_scripts +
                   "plot_timecomp.py " + filename_data)
    else:
        print("Do you already have a benchmark you want to plot? Default: no")
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

    if (os.path.isfile(path_data_ouput + "data_BB" + n)):
        system("mv " + path_data_output + "data_BB" +
               n + " " + path_data + "/data_BB" + n)

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

    # print("Do you want to delete general files? Default: no")
    # print("These files are in the folder GEN_data, and are the files containing time comparison and iterations.")
    # delete = input("[y/n] ")
    # if (delete == "y"):
    #     dirs = os.listdir(path_GEN)
    #     directory = []
    #     for _dir in dirs:
    #         if ("BB" in _dir):
    #             directory.append(_dir)
    #     delete_files(path_GEN, directory)

    print("Thank you... Have a nice day.")


if problem == "qd1e":
    filename_plot = "plot_QD_oneElectron"
    filename_data = "QD_oneElectron"
    path_data = "./QD_data"
    path_plot = "./QD_plot"

    print("QUANTUM DOTS ONE ELECTRON \n")

    # Create directories for output if not already exsisting
    create_directory([path_data, path_data_output, path_GEN])

    print("Enter desired tolerance: Default: 10^(-5)")
    tolerance = input("10^(-[int]) ")
    if (not tolerance.isdigit()):
        tolerance = str(5)
    print(f"Tolerance = 10^(-{tolerance:s})")

    print("Do you already have a dataset you want to evaluate? Default: yes")
    data_set = input("[y/n] ")
    if (data_set == "n"):
        print(r"What values for rho_max do you want? Default: [2:0.2:10]")
        rho_max = input("[double] ")
        if (not rho_max.isdigit()):
            rho_max = np.linspace(2, 10, 41)
        elif (isfloat(rho_max) or rho_max.isdigit()):
            print("Do you want more values for rho? Default: no")
            multi_rho = input("[y/n] ")
            if (multi_rho == "y"):
                rho_max = [rho_max]
                while True:
                    print("Do you want to add more values? Default: no")
                    value = input("[double] ")
                    if (value == "" or value == "n"):
                        break
                    if (isfloat(value) or value.isdigit()):
                        rho_max.append(value)
                    else:
                        print(
                            f"{value} is not an accepted value for rho. Please enter a float or int, if you don't want to add more values, press enter or n + enter.")

        # Set the rhovalues such that they can be appended to a string without causing sh faults
        prec = 10  # precision of numbers, currently 0.x, increase if you want to use i.e. 0.00x
        rho_names = []
        for i in range(len(rho_max)):
            rho_names.append(int(round(rho_max[i]*10)))

        print(
            "For what values of n do you want to iterate for? Default: [100, 200, 300, 400]")
        multi_n = input("[int] ")
        if (not multi_n.isdigit()):
            multi_n = [100, 200, 300, 400]
        elif (multi_n.isdigit()):
            print("Do you want to add more values for n? Default: no")
            value = input("[int] ")
            multi_n = [multi_n]
            if(value.isdigit()):
                while True:
                    if (not value.isdigit):
                        break
                    multi_n.append(value)
                    value = input("[int]")

        print(f"Running the program for n = {multi_n}")
        print("This takes a while, so be patient.")
        for i, rho in enumerate(rho_max):
            print(f"Current value for rho_max = {rho}")
            for n in multi_n:
                # "./cpp_codes/main {n} 1 {filename_data}{rho_max} 0 {rho_max} {tolerance} 1"
                system(path_cpp + " " + str(n) + " 1 " +
                       filename_data + str(rho_names[i]) + "_" + " 0 " + str(rho) + " " + tolerance + " 1")

    print("Finding the smallest values for rho and n, which satisfies the condition of the tolerance, if not satisfied, returns the smallest error.")
    system("python3 " + path_scripts + "eigenvalues_error.py " +
           filename_data + " " + tolerance)

    move_list = []
    with open(path_GEN + "eigenvalues_rho_n", 'r') as f:
        for lines in f:
            lines = lines.strip("(")
            lines = lines.strip(")\n")
            lines = lines.split(",")
            line = lines[-1]
            move_list.append(line.strip(" "))
    for string in move_list:
        if (os.path.isfile(path_data_output + "data_" + filename_data + string)):
            system("mv " + path_data_output + "data_" + filename_data +
                   string + " " + path_data + "/data_" + filename_data + string)

    print("Do you want to delete the output files? Default: yes")
    delete = input("[y/n] ")

    if (delete != "n"):
        # Asking if all files should be deleted or only spesific
        files = []
        print("Specify which files, if NONE, all are deleted: Default: NONE")
        while True:
            specific = input("[str] ")
            if (specific == "" or specific == "NONE"):
                break
            files.append(specific)
        if (not files):
            delete_files(path_data_output)
        else:
            delete_files(path_data_output, files)

    print("Do you want to delete general files? Default: no")
    print("These files are in the folder GEN_data, and are the files containing time comparison and iterations.")
    delete = input("[y/n] ")
    if (delete == "y"):
        dirs = os.listdir(path_GEN)
        directory = []
        for _dir in dirs:
            if ("QD" in _dir):
                directory.append(_dir)
            if directory:
                delete_files(path_GEN, directory)

    print("Thank you... Have a nice day.")
