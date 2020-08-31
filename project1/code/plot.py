#!/usr/bin python3
import matplotlib.pyplot as plt
import numpy as np
import sys
import os.path


def plot_file(in_file, out_file, skip_rows):
    [x, app, exa, rel] = read_file4(in_file, skip_rows)
    return -1


def read_file4(in_file, skip):
    if not os.path.isfile(in_file):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(in_file, skiprows=skip)
        return [data[:, 0], data[:, 1], data[:, 2], data[:, 3]]


def setup_figure():
    return -1


if __name__ == "__main__":
    in_file = sys.argv[1]
    out_file = sys.argv[2]
    skip_rows = int(sys.argv[3])
    plot_file(in_file, out_file, skip_rows)
    print("Success")
