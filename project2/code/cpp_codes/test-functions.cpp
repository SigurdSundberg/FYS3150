#include "catch.hpp"
#include "jacobi_rotation.h"

using namespace arma;

/*
    Checks wether the eigenvalues from the Toeplits matrix is set up correctly and 
    is the same as the analytical solutions 
*/
TEST_CASE("Testing analytical eigenvalues symmetrical toeplitz matrix, [base]")
{
    // Setup of initial variables
    int n = 3;
    double h = 1. / (n); // steplength
    double hh = h * h;
    mat A = zeros<mat>(n, n);
    mat R = eye<mat>(n, n);

    // Finding exact eigenvalues
    vec exact(n);
    double diagonal = 2.0 / hh;
    double non_diagonal = -1.0 / hh;
    double pi = acos(-1.0);
    for (int i = 0; i < n; i++)
    {
        exact(i) = diagonal + 2 * non_diagonal * cos((i + 1) * pi / (n + 1));
    }

    // Finding numerical values
    initialize(0, A, n, h);
    vec eigen_value_num = eig_sym(A);

    REQUIRE(eigen_value_num(0) == Approx(exact(0)).epsilon(0.00000001));
    REQUIRE(eigen_value_num(1) == Approx(exact(1)).epsilon(0.00000001));
    REQUIRE(eigen_value_num(2) == Approx(exact(2)).epsilon(0.00000001));
}

/*
    Finds the largest off diagonal element, of a matrix of dimensionality n.
    Matrix has to be symmetric, and tests wether the implementaiton is correct
*/
TEST_CASE("Finding max element, [base]")
{
    int n = 3;
    double pmin = 0, pmax = 10, h = (pmax - pmin) / (double(n));
    mat A = zeros<mat>(n, n);
    mat R = zeros<mat>(n, n);

    //initialize matrices and vector
    initialize(1, A, n, h);
    int p = 0;
    int q = 0;
    double max_ele = 0;

    //find maximum matrix element
    find_max_element(A, n, max_ele, p, q);

    REQUIRE(p == 1);
    REQUIRE(q == 2);
    REQUIRE(max_ele == Approx(0.09));
}

/*

Only implement if you have time, try to solve the rest of the problems on the report first 
TEST_CASE("Testing eigenvalues, [base]")
{
  
}
*/

/*
    Testing wether orthogonality is perserved after jacobi rotation.
*/
TEST_CASE("Testing eigenvector orthogonality, [base]")
{
    int n = 4, k = n - 1, l = n - 2;
    double pmin = 0, pmax = 10, h = (pmax - pmin) / (double(n)), max_ele = 0;
    mat A = zeros<mat>(n, n);
    mat R = eye<mat>(n, n);
    double tol = 1e-8;
    int interact = 0;
    int max_iter = n * n * n;
    vec v1(3);
    vec v2(3);
    vec v3(3);
    initialize(1, A, n, h);
    jacobi(A, R, n, tol, max_iter);

    /* 
        Extract the three vectors, and do the dot products of them. Use arma dot and t()
    */
    for (int i = 0; i < 3; i++)
    {
        v1(i) = R(0, i);
        v2(i) = R(1, i);
        v3(i) = R(2, i);
    }

    double dot1 = dot(v1, v2) + dot(v1, v3) + dot(v2, v3); // = 0
    double dot2 = dot(v1, v1) * dot(v2, v2) * dot(v3, v3); // = 1

    REQUIRE(dot1 == Approx(0.000).margin(0.01));  // Value close to 0
    REQUIRE(dot2 == Approx(1.000).epsilon(0.01)); // Values close to 1
}
