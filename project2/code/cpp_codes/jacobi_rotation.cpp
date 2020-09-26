/*
Spesification of functions 
*/

#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>

#include "jacobi_rotation.h"

using namespace std;
using namespace arma;

void jacobi(mat &A, mat &R, int n, double tol, int &max_iterations)
{
    int p = 0, q = 0, iterations = 0;
    double max_element = fabs(A(n - 1, n - 2));
    while (max_element > tol && iterations < max_iterations)
    {
        find_max_element(A, n, max_element, p, q);
        rotate_matrix(A, R, n, p, q);
        iterations++;

        // To keep track of iterations. And checking that the program doesn't freeze during testing.
        /*
        if (iterations % 500 == 0)
        {
            cout << iterations << endl;
        }
        */
    }
    // [1] Printing number of iterations for different n. (done)
    // cout << "n " << n << " iterations " << iterations << endl;
    max_iterations = iterations;
}

/* 
    ** The function
    **      initialize()
    ** takes an argument for what type of matrix is should set up
    ** as interact, and a zero matrix A, a zero matrix eig_vec
    ** which are both initialized and the size of the matricies n
    ** and the steplength of h of the problem. 
    ** Set matrix A and eig_vec to their respective matricies. 
*/
void initialize(int interact, mat &A, int n, double h)
{
    double diagonal, non_diagonal, hh = h * h;
    diagonal = 2. / (hh);
    non_diagonal = -1. / (hh);
    vec rho(n);
    // Not used
    // double wr;
    // double wrr = wr * wr;
    /* 
    Create the eigenvector matrix. Initialized to the orthogonal matrx
    being the identity matrix(Depricated)
    
    for (int i = 0; i < n; i++)
    {
        R(i, i) = 1;
    }
    */

    /*
    Create vector of rho values if problem is not 0[bb]
    */
    if (interact != 0)
    {

        rho(0) = h;
        for (int i = 1; i < n; i++)
        {
            rho(i) = rho(i - 1) + h;
        }
    }

    /*
    Setup the Tridiagonal toeplitz matrix
    */
    if (interact == 0) // Buckling beam
    {
        A(0, 0) = diagonal;
        A(0, 1) = non_diagonal;
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i) = diagonal;
            A(i, i - 1) = non_diagonal;
            A(i, i + 1) = non_diagonal;
        }
        A(n - 1, n - 1) = diagonal;
        A(n - 1, n - 2) = non_diagonal;
    }
    else if (interact == 1) // QD One electron
    {
        A(0, 0) = diagonal + rho(0) * rho(0);
        A(0, 1) = non_diagonal;
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i) = diagonal + rho(i) * rho(i);
            A(i, i - 1) = non_diagonal;
            A(i, i + 1) = non_diagonal;
        }
        A(n - 1, n - 1) = diagonal + rho(n - 1) * rho(n - 1);
        A(n - 1, n - 2) = non_diagonal;
    }
    // else if (interact == 2) // QD Two electrons
    // {
    //     A(0, 0) = diagonal + wrr * rho(0) * rho(0) + 1. / rho(0);
    //     A(0, 1) = non_diagonal;
    //     for (int i = 1; i < n - 1; i++)
    //     {
    //         A(i, i) = diagonal + wrr * rho(i) * rho(i) + 1. / rho(i);
    //         A(i, i - 1) = non_diagonal;
    //         A(i, i + 1) = non_diagonal;
    //     }
    //     A(n - 1, n - 1) = diagonal + wrr * rho(n - 1) * rho(n - 1) + 1. / rho(n - 1);
    //     A(n - 1, n - 2) = non_diagonal;
    // }
} // End: function initialize()

/*
    ** The function
    **    find_max_element()
    ** takes as input an nxn armadillo matrix
    ** two indicies p(row) and q(column) and an
    ** integer n which is the size of the matrix.
    ** Finds the largest non-diagonal element of the matrix
    ** and returns its indicies.
*/
void find_max_element(mat A, int n, double &max_element, int &p, int &q)
{
    max_element = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double current_element = fabs(A(i, j));
            if (current_element >= max_element)
            {
                p = i;
                q = j;
                max_element = current_element;
            }
        }
    }
} // End: function max_Offdiagonal_element

void rotate_matrix(mat &A, mat &R, int n, int k, int l)
{
    double s, c;
    if (A(k, l) != 0.0)
    {
        double tau, t;
        tau = (A(l, l) - A(k, k)) / (2.0 * A(k, l));
        if (tau >= 0)
        {
            t = 1.0 / (tau + sqrt(1.0 + tau * tau));
        }
        else
        {
            t = -1.0 / (-tau + sqrt(1.0 + tau * tau));
        }
        c = 1.0 / sqrt(1.0 + t * t);
        s = t * c;
    }
    else
    {
        c = 1.0;
        s = 0.0;
    }
    // Setup the new elements
    double a_ik, a_il, a_kk, a_ll, a_kl, r_ik, r_il;
    a_kk = A(k, k);
    a_ll = A(l, l);
    a_kl = A(k, l);
    A(k, k) = (a_kk * c * c) - (2 * c * s * a_kl) + (a_ll * s * s);
    A(l, l) = (a_ll * c * c) + (2 * c * s * a_kl) + (a_kk * s * s);
    A(k, l) = 0.0;
    A(l, k) = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (i != k && i != l)
        {
            a_ik = A(i, k);
            a_il = A(i, l);
            A(i, k) = a_ik * c - a_il * s;
            A(i, l) = a_il * c + a_ik * s;
            A(k, i) = A(i, k);
            A(l, i) = A(i, l);
        }
        r_ik = R(i, k);
        r_il = R(i, l);
        R(i, k) = c * r_ik - s * r_il;
        R(i, l) = c * r_il + s * r_ik;
    }
} // End: function rotate_matrix()

/*
void test_OrthogonalityPreservation(mat A, mat S, int n)
{
    /* code 
}
/*
    ** The function
    **      test_ConservationOfEigenvalues()
    ** takes the numerical/analytical eigenvalues and
    ** compares them to the numerical found in matrix A
    ** after undergoing jacobi rotation. 
    ** Input is the diagonalized verison of A
    ** prefound eigen values and grid size n. 
    
void test_ConservationOfEigenvalues(mat A, vec v, int n)
{
    vec eigen_values;
    mat tmp;
    eigen_values = diagvec(A);
    for (int i = 0; i < n; i++)
    {
        if (fabs(eigen_values(i) - v(i)) > 1e-5)
        {
            cout << "Eigenvalues are not conserved" << endl;
            exit(1);
        }
    }
} // End: function test_ConservationOfEigenvalues()

void test_JacobiRotation()
{
    /* code 
}

/* 
    ** The test function
    **      test_Largest_diagonal_element
    ** takes a matrix A, the size of A and the expected value 
    ** and determines wether the function finds the largest element. 
    
void test_Largest_diagonal_element(mat A, int n, int value)
{
    // Initialzise needed variables
    double element = -99.;
    int p = 0;
    int q = 0;
    // calling the function to test
    max_Offdiagonal_element(A, element, p, q, n);
    // Setting the found value and checking if it is close enough to the expected value
    double found_value;
    found_value = A(p, q);
    if (fabs(found_value - value) > 1e-12)
    {
        cout << "Problem finding largest offdiagonal element" << endl;
        cout << "value found = " << setw(8) << setprecision(15) << found_value << endl;
        cout << "expected value = " << setw(8) << setprecision(15) << value << endl;
        exit(1)
    }
} // End: function test_Largest_diagonal_element
*/