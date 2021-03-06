#include <cstdlib>  // atof function: ASCII to Float
#include <iostream> // cout
#include <cmath>    // math functions
#include <fstream>  // Input/output stream class to operate on files.
#include <iomanip>  // Set parametric such as setw, setprecision
#include <string>   // Add normal string functionality
#include <chrono>   // timing program'
// using namespace std for input and output
using namespace std;

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

        // Defining steplength and steplength ^2
        double h = 1.0 / (n);
        double hh = h * h;
        // Defining variables and vectors
        double quotient;
        double *x = new double[n + 1];      // x\in(0,1)
        double *a = new double[n + 1];      // vector of lower diag elements
        double *b = new double[n + 1];      // vector of diag elements
        double *c = new double[n + 1];      // vector of upper diag elements
        double *f_star = new double[n + 1]; // answer from explicit function

        // double *b_tilde = new double[n + 1];  // leading diag after for sub
        double *f_tilde = new double[n + 1];  // answer vec after first pass
        double *solution = new double[n + 1]; // solution of the set of equations

        // setup of vector elements
        solution[0] = solution[n] = 0;

        // b_tilde[1] = 2; // b[i] = b_tilde[i]

        for (int i = 0; i <= n; i++)
        {
            a[i] = -1.0;
            c[i] = -1.0;
            b[i] = 2.0;
            x[i] = i * h;
            f_star[i] = hh * f(i * h);
        }
        f_tilde[1] = f_star[1];

        // start timing
        auto start = chrono::high_resolution_clock::now();

        // Implementation of algorithm
        // Forwards substituti  on
        // writing over the elements on b instead of implementing a new vector b_tilde. Both are equally valid. And computaionally only a net positive.
        for (int i = 2; i < n + 1; i++)
        {
            quotient = a[i - 1] / (double)b[i - 1];             // first element of b[i] = b_tilde[i]
            b[i] = b[i] - c[i - 1] * quotient;                  //quotient;
            f_tilde[i] = f_star[i] - f_tilde[i - 1] * quotient; //quotient;
        }
        solution[n - 1] = f_tilde[n - 1] / b[n - 1];
        for (int i = n - 2; i > 0; i--)
        {
            solution[i] = (f_tilde[i] - solution[i + 1] * c[i]) / b[i];
        }

        // end timing
        auto finish = chrono::high_resolution_clock::now();

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

        // Free memory
        delete[] x;
        delete[] a;
        delete[] b;
        delete[] c;
        delete[] f_star;
        delete[] f_tilde;
        // delete[] b_tilde;
        delete[] solution;
    }

    return 0;
}
