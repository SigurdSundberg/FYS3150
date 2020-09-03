#include <cstdlib>   // atof function: ASCII to Float
#include <iostream>  // cout
#include <cmath>     // math functions
#include <fstream>   // Input/output stream class to operate on files.
#include <iomanip>   // Set parametric such as setw, setprecision
#include <string>    // Add normal string functionality
#include <ctime>     // timing program'
#include <armadillo> // armadillo lib used to manip vectors and matricies

// using namespace std for input and output
using namespace std;
using namespace arma;

// object for output files
ofstream ofile;

//functions used
double f(double x)
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

        //Initialization of vectors
        double h = 1.0 / (n);
        double hh = h * h;
        // shift the matrix so only the part between the endpoints is studied
        n = n - 1; // n n-1
        mat A = zeros<mat>(n, n);
        vec f(n);
        // vec x(n);
        A(0, 0) = 2;
        A(0, 1) = -1;
        // x(0) = h;
        f(0) = hh * f(x(0));
        for (int i = 1; i < n - 1; i++)
        {
            // x(i) = x(i - 1) + h;
            f(i) = hh * f(x(i));
            A(i, i - 1) = -1;
            A(i, i + 1) = -1;
            A(i, i) = 2;
        }
        A(n - 1, n - 1) = 2;
        A(n - 2, n - 1) = -1;
        // x(n - 1) = x(n - 2) + h;
        f(n - 1) = hh * f(x(n - 1));

        // start timing
        clock_t start, finish;
        start = clock();

        // Using armadillo solve to solve the problem
        vec solution = solve(A, f);

        // end timing
        finish = clock();

        // Output to file
        /*        ofile.open("./output/" + fileout);
         // formatting of output
        ofile << setiosflags(ios::showpoint | ios::uppercase);
        // title header of output file
        ofile << "           x:          approx:          exact:     relative error:" << endl;
        ofile << "program : " << argv[0] << endl;
        for (int i = 1; i < n; i++)
        {
            double xval = x[i];
            double relative_error = fabs((exact(xval) - solution[i]) / exact(xval));
            ofile << setw(15) << setprecision(8) << xval;
            ofile << setw(15) << setprecision(8) << solution[i];
            ofile << setw(15) << setprecision(8) << exact(xval);
            ofile << setw(15) << setprecision(8) << log10(relative_error) << endl;
        }
        ofile.close(); */

        // Writing to time_file
        ofile.open("./output/" + time_fileout);
        double timeused = (double)(finish - start) / ((double)CLOCKS_PER_SEC);
        ofile << "Program tested = " << argv[0] << " for power of 10^" << argument << endl;
        ofile << setprecision(10) << setw(20) << "Time used for computation = " << timeused << endl;
        ofile.close();
    }

    return 0;
}
