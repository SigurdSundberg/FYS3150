#include "catch.hpp"
#include "jacobi_rotation.h"

using namespace arma;

TEST_CASE("Testing analytical eigenvalues symmetrical toeplitz matrix, [base]")
{
    // Setup of initial variables
    int n = 3;
    double h = 1. / n; // steplength
    double hh = h * h;
    mat A = zeros<mat>(n, n);
    mat R = zeros<mat>(n, n);

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
    initialize(0, A, R, n, h);
    vec eigen_value_num = eig_sym(A);

    REQUIRE(eigen_value_num(0) == Approx(exact(0)).epsilon(0.00000001));
    REQUIRE(eigen_value_num(1) == Approx(exact(1)).epsilon(0.00000001));
    REQUIRE(eigen_value_num(2) == Approx(exact(2)).epsilon(0.00000001));
}

TEST_CASE("Finding max element, [base]")
{
    int n = 3;
    double pmin = 0, pmax = 10, h = (pmax - pmin) / (double(n));
    mat A = zeros<mat>(n, n);
    mat R = zeros<mat>(n, n);

    //initialize matrices and vector
    initialize(1, A, R, n, h);
    int p = 0;
    int q = 0;
    double max_ele = 0;

    //find maximum matrix element
    find_max_element(A, n, max_ele, p, q);

    REQUIRE(p == 1);
    REQUIRE(q == 2);
    REQUIRE(max_ele == Approx(0.09));
}

TEST_CASE("Testing eigenvalues, [base]")
{
    /*code*/
}

TEST_CASE("Testing eigenvector orthogonality, [base]")
{
    /* code */
}