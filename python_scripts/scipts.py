import os
import numpy as np


def get_directory(path, problem):
    dirs = os.listdir(path)
    directory = []
    for _dir in dirs:
        if (problem in _dir):
            directory.append(_dir.strip(problem))
    return directory


def read_file(path):
    """Spesific function for reading a spesific data file
    """
    if not os.path.isfile(path):
        print("File does not exists")
        sys.exit(1)
    else:
        data = np.loadtxt(path, max_rows=1)
        return data


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
