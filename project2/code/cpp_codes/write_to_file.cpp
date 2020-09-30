#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <armadillo>

#include "write_to_file.h"

using namespace arma;
using namespace std;

ofstream ofile;

/*
    This takes a matrix and a vector and writes them to file on the form 
    eigenvalues 
    eigenvectors as column vectors underneath  the accompanying eigenvalues
*/
void write_to_file_data(string filename, vec v_data, mat M_data)
{
    double values;
    ofstream ofile;
    ofile.open("./cpp_codes/output/" + filename, ios_base::out);
    ofile << setiosflags(ios::scientific);
    if (ofile.is_open())
    {
        // ofile << "File successfully open";
        int n = v_data.n_elem;
        for (int i = 0; i < n; i++)
        {
            ofile << setw(15) << v_data(i);
        }
        ofile << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                values = M_data(0, j);
                if (values <= 0)
                {
                    ofile << setw(15) << M_data(i, j) * (-1);
                }
                else
                {
                    ofile << setw(15) << M_data(i, j);
                }
            }
            ofile << endl;
        }
        ofile.close();
    }
    else
    {
        cout << "Error opening file";
    }
}

/*
    Writes the value of n and the number of iterations for that value of n for a given dataset 
    This does not delete the file, only appends to an exsisting file 
*/
void write_to_file_iterations(string filename, int n, int iterations)
{
    ofile.open("./GEN_data/time_iterations_" + filename, ios_base::app);
    ofile << setw(3) << n << setw(15) << iterations << endl;
    ofile.close();
}

/*
    Writes the an n A B C to a file, where the inputs are single numbers. 
    IT does not delete the file on appends the data to the file 
*/
void write_to_file_time(string filename, double A, double B, double C, int n)
{
    ofile.open("./GEN_data/" + filename, ios_base::app);
    ofile << setw(3) << n << setw(15) << A << setw(15) << B << setw(15) << C << endl;
    ofile.close();
}