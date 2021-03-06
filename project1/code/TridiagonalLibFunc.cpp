#include <cstdlib>  // atof function: ASCII to Float
#include <iostream> // cout
#include <cmath>    // math functions
#include <fstream>  // Input/output stream class to operate on files.
#include <iomanip>  // Set parametric such as setw, setprecision
#include <string>   // Add normal string functionality
#include <chrono>   // timing program'
#include "lib.hpp"  // library functions used in FYS3150

// using namespace std for input and output
using namespace std;

// object for output files
ofstream ofile;

//functions used

// double derivative of u by x
double ddu(double x)
{
    // Given function f
    return 100.0 * exp(-10.0 * x);
}

double exact(double x)
{
    // Given function u
    return 1.0 - (1 - exp(-10)) * x - exp(-10 * x);
}

int main(int argc, char *argv[])
{
    // input handeling
    // reading output base file name and highest exponent
    int exponent;
    string filename;
    if (argc <= 1)
    {
        cout << "Bad usage: " << argv[0] << " read also filename and highest power exponent" << endl;
        exit(1);
    }
    else
    {
        filename = argv[1];       // filename as first input
        exponent = atoi(argv[2]); // power of exponent
    }

    // looping over all the exponents, from 1 to highest exponent
    for (int i = 1; i <= exponent; i++)
    {
        //cout << i << endl;
        // length of the arrays n elements
        int n = (int)pow(10.0, i);
        // Base extension of filename
        string fileout = filename;
        // end extension of filenames powers of 10, i.e. 1, 2, 3, ...
        string argument = to_string(i);
        // full filename on the form filename-i-
        fileout.append(argument);
        // timing file
        string time_fileout = "timed_" + fileout;

        // setting up matricies and vectors
        double **A = (double **)matrix(n, n, sizeof(double));
        int *indx = new int[n];
        double *solution = new double[n];
        double d;
        double *x = new double[n];

        double h = 1.0 / (n - 1);
        double hh = h * h;

        // setup values in matricies and vectors
        A[0][0] = 2.;
        A[0][1] = -1.;
        for (int i = 1; i < n - 1; i++)
        {
            A[i][i] = 2;
            A[i][i + 1] = -1.;
            A[i][i - 1] = -1.;
        }
        A[n - 1][n - 1] = 2.;
        A[n - 1][n - 2] = -1.;
        for (int i = 0; i <= n; i++)
        {
            x[i] = h * (i + 1);
            solution[i] = hh * ddu(x[i]);
        }
        //cout << "done setup" << endl;
        // start timing
        auto start = chrono::high_resolution_clock::now();

        // LU dcmp and LU back sub
        ludcmp(A, n, indx, &d);
        // cout << "decomp" << endl;
        lubksb(A, n, indx, solution);

        // end timing
        auto finish = chrono::high_resolution_clock::now();
        // cout << "done calc" << endl;
        // Output to file
        ofile.open("./output/" + fileout);
        // formatting of output
        ofile << setiosflags(ios::scientific);
        // title header of output file
        ofile << "              x:             approx:              exact:         relative error:" << endl;
        ofile << "program : " << argv[0] << endl;
        for (int i = 0; i < n + 1; i++)
        {
            double xval = x[i];
            double relative_error = fabs((exact(xval) - solution[i]) / exact(xval));
            if (isnan(relative_error) || isinf(relative_error))
            {
                relative_error = -99;
            }
            else
            {
                relative_error = log10(relative_error);
            }
            ofile << setw(20) << setprecision(8) << xval;
            ofile << setw(20) << setprecision(8) << solution[i];
            ofile << setw(20) << setprecision(8) << exact(xval);
            ofile << setw(20) << setprecision(8) << relative_error << endl;
        }
        ofile.close();

        // Writing to time_file
        ofile.open("./output/" + time_fileout);
        ofile << "Program tested = " << argv[0] << " for power of 10^" << argument << endl;
        ofile << setprecision(10) << setw(20) << "Time used for computation in seconds = " << endl;
        ofile << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9) << endl;
        ofile.close();

        free_matrix((void **)A);
        delete[] indx;
        delete[] x;
        delete[] solution;
    }

    return 0;
}
