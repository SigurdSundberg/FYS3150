#include <cstdlib>  // atof function: ASCII to Float
#include <iostream> // cout
#include <cmath>    // math functions
#include <fstream>  // Input/output stream class to operate on files.
#include <iomanip>  // Set parametric such as setw, setprecision
#include <string>   // Add normal string functionality
#include <ctime>    // timing program
// using namespace std for input and output
using namespace std;

// object for output file
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

        // initialization of vectors and constants
        // double const e = -1;
        double h = 1.0 / (n);
        double hh = h * h;
        double *d = new double[n + 1];
        double *f_star = new double[n + 1];   // couldve used two arrays, using one to save space
        double *x = new double[n + 1];        // x\in(0,1)
        double *solution = new double[n + 1]; // solution
        d[0] = 2;
        solution[0] = solution[n] = 0.0;
        for (int i = 1; i < n; i++)
        {
            // pre calc of d
            d[i] = (i + 1.0) / ((double)i);
        }
        for (int i = 0; i <= n; i++)
        {
            // setup xi and f_star
            x[i] = i * h;
            f_star[i] = hh * f(i * h);
        }

        // start timing
        clock_t start, finish;
        start = clock();

        // implementation of algortihms
        // forward sub
        for (int i = 2; i < n; i++)
        {
            f_star[i] = f_star[i] + f_star[i - 1] / d[i - 1];
        }
        solution[n - 1] = f_star[n - 1] / d[n - 1];
        for (int i = n - 2; i > 0; i--)
        {
            solution[i] = (f_star[i] + solution[i + 1]) / d[i];
        }

        // end timing
        finish = clock();

        // Output to file
        ofile.open("./output/" + fileout);
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
        ofile.close();

        // Writing to time_file
        ofile.open("./output/" + time_fileout);
        double timeused = (double)(finish - start) / ((double)CLOCKS_PER_SEC);
        ofile << "Program tested = " << argv[0] << " for power of 10^" << argument << endl;
        ofile << setprecision(10) << setw(20) << "Time used for computation = " << timeused << endl;
        ofile.close();

        delete[] x;
        delete[] solution;
        delete[] f_star;
        delete[] d;
    }

    return 0;
}
