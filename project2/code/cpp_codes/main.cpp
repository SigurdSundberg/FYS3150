#include <armadillo>
#include <chrono>

#include "functions.h" // Placeholder name, use if nothing better comes to mind
using namespace arma;
using namespace std;

// Very basic code

void jacobi_rotation(mat A, mat R, int k, int l, int n)
{
    /* code */
}

void cst()
// This should be implemented in jacobi_rotation later on, and not left as it's own function. Could be if need be
{
    double s, c;
    if (A(k, l) != 0, 0)
    {
        double tau, t;
        // Following should be in a for-loop
        tau = (A(l, l) - A(j, j)) / A(j, l); // Values for tau
        if (True)
        {
            t = tau; //...
        }
        else
        {
            t = tau; //...
        }
        c = 1 / sqrt(1 + t * t);
        s = t * c;
    }
    else
    {
        c = 1.0;
        s = 0.0;
    }
}

void main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
