#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>

#include "jacobi_rotation.h"

using namespace arma;
using namespace std;

ofstream ofile;

// void write_to_file(string filename, vec data)
// {
//     ofstream ofile;
//     ofile.open("./output/" + filename);
//     ofile << setiosflags(ios::scientific);
//     int n = data.n_elem;
//     for (int i = 0; i < n; i++)
//     {
//         ofile << data(i) << endl;
//     }
// }

int main(int argc, char const *argv[])
{
    int max_iterations, iterations, n, p, q, interact;
    double epsilon, max_element, h, xmin, xmax;
    string filename;

    // Setting input arguments from command line to respective values
    if (argc <= 5)
    {
        cout << "Bad usage: " << argv[0] << "number of meshgrid points, max iterations and type of problem, and filename" << endl;
        exit(1);
    }
    else
    {
        n = atoi(argv[1]);
        interact = atoi(argv[2]);
        filename = argv[3];
        xmin = atoi(argv[4]);
        xmin = atoi(argv[5]);
    }
    cout << "Interact: " << interact << endl; // 0, 1, 2. [BB], [QD 1], [QD 2]

    // Defining our initial constants and matricies
    mat A = zeros<mat>(n, n);
    mat R = eye<mat>(n, n);

    iterations = 0;
    max_iterations = n * n * n; // Upper limit, expectation is of O(n*n)
    p = 0;                      // ROw element
    q = 0;                      // Column element
    epsilon = 1e-12;            // Convergence tolerance

    h = (xmax - xmin) / (double(n)); // Steplength

    // initializing the problem
    initialize(interact, A, n, h);
    max_element = fabs(A(n - 1, n - 2)); // choosing the last off diagonal element

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

    /* (This is implemented in the jacobi function, for easier use)
    while (max_element > epsilon && iterations < max_iterations)
    {
        find_max_element(A, n, max_element, p, q);
        rotate_matrix(A, R, n, p, q);

        // To keep track of iterations.
        iterations++;
        if (iterations % 500 == 0)
        {
            cout << iterations << endl;
        }
    }*/

    auto finish = chrono::high_resolution_clock::now();

    /*
        Printing the time used by both Armadillo and Jacobi's method
        Creating a vector to include both data values
        Create a new filename for time file
        Write to file
    */
    cout << "Time used for n = " << n << " in seconds" << endl;
    double time_Armadillo = chrono::duration_cast<chrono::nanoseconds>(finishA - startA).count() / pow(10, 9);
    cout << "Armadillo " << time_Armadillo << endl;

    double time_Jacobi = chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9);
    cout << "JacobisMethod " << time_Jacobi << endl;
    // cout << "Number of iterations " << iterations << endl; // Implemented in jacobi()

    // string time_filename = "time_J_A_" + filename;
    // ofile.open("./output/" + time_filename);
    // ofile << setiosflags(ios::scientific);
    // ofile << "Armadillo " << time_Armadillo << endl;
    // ofile << "JacobiMethod " << time_Jacobi << endl;
    // ofile.close();

    return 0;
}

// ofile << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9) << endl;