/*
Spesification of functions 
*/

#include <iostream>
#include <iomanip>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

/*
    ** The function
    **    void max_Offdiagonal_element()
    ** takes as input an nxn armadillo matrix
    ** two indicies p(row) and q(column) and an
    ** integer n which is the size of the matrix.
    ** Finds the largest non-diagonal element of the matrix
    ** and returns its indicies.
*/
void max_Offdiagonal_element(mat A, double &max_element, int &p, int &q, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double current_element = fabs(A(i, j));
            if (current_element > max_element)
            {
                p = i;
                q = j;
                max_element = current_element;
            }
        }
    }
} // End: function max_Offdiagonal_element

void rotate_matrix(mat A, mat R, int n, int k, int l)
{
    double s, c;
    if (A(k, l) != 0.0)
    {
        double tau, t;
        tau = (A(l, l) - A(k, k) / (2.0 * A(k, l)));
        if (tau >= 0)
        {
            t = 1.0 / (tau + sqrt(1 + tau * tau));
        }
        else
        {
            t = -1.0 / (-tau + sqrt(1 + tau * tau));
        }
        c = 1.0 / sqrt(1.0 + t * t);
        s = t * c;
    }
    else
    {
        c = 1.0;
        s = 0.0;
    }
    // Setu the new elements
    double a_ik, a_il, a_kk, a_ll, r_ik, r_il;
    a_kk = A(k, k);
    a_ll = A(l, l);
    A(k, k) = (a_kk * c * c) - (2 * c * s * A(k, l)) + (a_ll * s * s);
    A(l, l) = (a_ll * c * c) + (2 * c * s * A(k, l)) + (a_kk * s * s);
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
            A(i, l) = A(l, i);
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
    /* code */
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
    /* code */
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