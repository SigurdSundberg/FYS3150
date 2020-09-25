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

void write_to_file_data(string filename, vec v_data, mat M_data)
{
    double values;
    ofstream ofile;
    ofile.open("./output/" + filename, ios_base::out);
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

void write_to_file_iterations(string filename, int n, int iterations)
{
    ofile.open("../data/time_iterations_" + filename, ios_base::app);
    ofile << setw(3) << n << setw(15) << iterations << endl;
    ofile.close();
}

void write_to_file_time(string filename, double A, double B, double C, int n)
{
    ofile.open("../data/" + filename, ios_base::app);
    ofile << setw(3) << n << setw(15) << A << setw(15) << B << setw(15) << C << endl;
    ofile.close();
}