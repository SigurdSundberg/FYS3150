#include <armadillo>
#include <chrono>
#include <cmath>
#include <string>

#include "jacobi_rotation.h"

using namespace arma;
using namespace std;

int main(int argc, char const *argv[])
{
    int max_iterations, iterations, n, p, q, interact;
    double epsilon, max_element, h, xmin, xmax;
    string filename;

    // Setting input arguments from command line to respective values
    if (argc <= 6)
    {
        cout << "Bad usage: " << argv[0] << "number of meshgrid points, max iterations and type of problem, and filename" << endl;
        exit(1);
    }
    else
    {
        n = atoi(argv[1]);
        max_iterations = atoi(argv[2]);
        interact = atoi(argv[3]);
        filename = argv[4];
        xmin = atoi(argv[5]);
        xmin = atoi(argv[6]);
    }

    // Defining our initial constants and matricies
    mat A = zeros<mat>(n, n);
    mat R = zeros<mat>(n, n);

    iterations = 0;
    p = 0;
    q = 0;
    epsilon = 1e-8;

    h = (xmax - xmin) / (double(n));

    // initializing the problem
    initialize(interact, A, R, n, h);
    max_element = fabs(A(n - 1, n - 2)); // choosing the last off diagonal element

    /*
        Using Armadillos eigensolver for symmetrical matricies
        Timing it for comparison
    */
    auto startA = chrono::high_resolution_clock::now();
    vec eigen_values_arma = eig_sym(A);
    auto finishA = chrono::high_resolution_clock::now();

    /*
        Start of the Jacobi rotations method
        With timing
    */
    auto start = chrono::high_resolution_clock::now();
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
    }
    auto finish = chrono::high_resolution_clock::now();

    /* 
        Printing the time used by both Armadillo and Jacobi's method 
        Creating a vector to include both data values 
        Create a new filename for time file
        Write to file 
    */
    double time_Armadillo = chrono::duration_cast<chrono::nanoseconds>(finishA - startA).count() / pow(10, 9);
    cout << "Time used by Armadillo's eigenvalue solver:" << endl;
    cout << "Time used for n = " << n << ": " << time_Armadillo << "s" << endl;

    double time_Jacobi = chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9);
    cout << "Time used by Jacobi's method:" << endl;
    cout << "Time used for n = " << n << ": " << time_Jacobi << "s" << endl;
    cout << "Number of iterations " << iterations << endl;

    vec data;
    data << time_Jacobi << time_Armadillo;
    string time_filename = "time_J_A_" + filename;
    write_to_file(time_filename, data);

    /* 
        Explanation of next part 
    */
    return 0;
}

// ofile << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9) << endl;