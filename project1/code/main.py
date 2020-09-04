from os import system
import sys


if __name__ == "__main__":
    # Initialization
    try:
        n = sys.argv[1]
        algo = sys.argv[2]
    except:
        print("Wrong use, include highest number of 10^n you need and algorithm name. \n")
        print("Example: python3 main.py n algo")

    if algo == "general":
        program = "General"
    if algo == "special":
        program = "Specialized"
    if algo == "lu":
        program = "LUDecomp"
    if algo == "lib":
        program = "LibFunc"

    print("Compiling...")
    if algo == "lu":
        system("c++ -O2 -o Tridiagonal" + program +
               ".x " + "Tridiagonal" + program +
               ".cpp -larmadillo -llapack -lblas")
    else:
        system("c++ -O2 -o Tridiagonal" + program +
               ".x " + "Tridiagonal" + program + ".cpp")
    print("Done compiling")

    # Run the programs
    print("Running code...")
    system("./Tridiagonal" + program + ".x" + " "
           + algo + " " + str(n))

    print("Calculations are done, making plots...")

    # Creating plots
    print("How many files do you want to plot from? type: int")
    # max_files = (input())  # Can hard code max files
    max_files = 3
    system("python3" + " " + "make_plot.py" + " "
           + algo + " " + max_files)

    print("Plots are done, finding maximum relative error...")
    # Relative error
    system("python3" + " " + "rel_err.py" + " "
           + algo + " " + n)

    print("Done creating maximum relative error file, making table over run times...")
    # Table over run times
    system("python3" + " " + "time_table.py" + " "
           + algo + " " + n)

    print("Done making table. ")

    # Removing files that aren't needed anymore
    print("Do you want to remove the output files?")
    # delete_files = input("y or n\n")
    delete_files = "y"
    if delete_files == "y":
        system("python3" + " " + "delete_files.py" + " "
               + algo + " " + n)

    print("Done\n")

    """
    run example: 
    python3 main.py 7 general
    """
