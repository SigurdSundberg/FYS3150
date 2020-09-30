#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>

#include "jacobi_rotation.h"
#include "write_to_file.h"
#include "bisection_method.h"

using namespace arma;
using namespace std;

int main(int argc, char const *argv[])
{
    int max_iterations, iterations, n, p, q, interact, tol, dataset;
    double epsilon, max_element, h, xmin, xmax;
    string filename;

    // Setting input arguments from command line to respective values
    if (argc < 8)
    {
        cout << argc << endl;
        cout << "Bad usage: " << argv[0] << " number of meshgrid points, max iterations and type of problem, and filename" << endl;
        exit(1);
    }
    else
    {
        n = atoi(argv[1]);
        interact = atoi(argv[2]);
        filename = argv[3];
        xmin = atof(argv[4]);
        xmax = atof(argv[5]);
        tol = atoi(argv[6]);
        dataset = atoi(argv[7]);
    }
    // cout << "Interact: " << interact << endl; // 0, 1, 2. [BB], [QD 1], [QD 2]

    // Defining our initial constants and matricies
    mat A = zeros<mat>(n, n);
    mat R = eye<mat>(n, n);
    iterations = 0;
    max_iterations = n * n * n;      // Upper limit, expectation is of O(n*n)
    p = 0;                           // Row element
    q = 0;                           // Column element
    epsilon = pow(10, -tol);         // Convergence tolerance
    h = (xmax - xmin) / (double(n)); // Steplength

    // initializing the problem
    initialize(interact, A, n, h);

    /*
        Using Armadillos eigensolver for symmetrical matricies
        Timing it for comparison
    */
    auto startA = chrono::high_resolution_clock::now();
    vec eigen_values_arma = eig_sym(A); // Just returns Eigen values
    auto finishA = chrono::high_resolution_clock::now();

    /*
        Start of the Jacobi rotations method
        With timing
    */
    auto start = chrono::high_resolution_clock::now();

    jacobi(A, R, n, epsilon, max_iterations);

    auto finish = chrono::high_resolution_clock::now();

    /*
        Bisection method
        n_bi is returned as the number of iterations
        tolerance is returned as worst case error
    */

    int n_bi = n;
    vec diagonal(n_bi), offdiagonal(n_bi), v(n_bi);
    initialize_bi(0, diagonal, offdiagonal, n_bi, h);
    double tolerance = 1e-12;

    auto startBi = chrono::high_resolution_clock::now();
    bisect(diagonal, offdiagonal, v, tolerance, n_bi);
    auto finishBi = chrono::high_resolution_clock::now();
    // cout << "Maximum error for bisection: " << tolerance << endl;

    /* 
        This set of data, are not subject to cold starts
        and is only calculated once if called for
    */
    if (dataset == 1)
    {
        // Write eigenvectors and eigenvalues to file.
        string data_filename = "data_" + filename + to_string(n);
        vec A_eig = diagvec(A);
        write_to_file_data(data_filename, A_eig, R);

        // Files for iterations
        string iter_filename_ja = "ja_" + filename;
        string iter_filename_bi = "bi_" + filename;
        write_to_file_iterations(iter_filename_ja, n, max_iterations);
        write_to_file_iterations(iter_filename_bi, n, n_bi);
    }

    /*
        This dataset is subject to cold starts and when called for
        is calculated multiple over multiple runs 
    */
    if (dataset == 2)
    {
        /*
        Printing the time used by both Armadillo and Jacobi's method
        Creating a vector to include both data values
        Create a new filename for time file
        Write to file
        */
        string time_filename = "time_Comparison_" + filename;

        double time_Armadillo = chrono::duration_cast<chrono::nanoseconds>(finishA - startA).count() / pow(10, 9);
        double time_Jacobi = chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9);
        double time_Bisection = chrono::duration_cast<chrono::nanoseconds>(finishBi - startBi).count() / pow(10, 9);
        // cout << " " << endl;
        // cout << setw(3) << "n " << setw(15) << "Armadillo" << setw(15) << "JacobisMethod" << endl;
        // cout << setw(3) << n << setw(15) << time_Armadillo << setw(15) << time_Jacobi << endl;
        // cout << " " << endl;

        // Uncomment this if you want to write to file
        write_to_file_time(time_filename, time_Armadillo, time_Jacobi, time_Bisection, n);
    }

    return 0;
}
