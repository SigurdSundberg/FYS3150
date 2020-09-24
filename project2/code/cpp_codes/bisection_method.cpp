#include <armadillo>
#include <cfloat>
#include <cmath>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>

#include "bisection_method.h"

using namespace arma;
using namespace std;

void bisect(vec &diagonal, vec &offdiagonal, vec &v, double &relative_tolerance, int &n)
{
    /*
        Gerschorin's theorem to find Upper and Lower bounds for all Eigenvalues
        Extreme bounds for upper and lower values of lambda
    */

    double xmax, xmin; // Extreme bounds for eigenvalues
    double h;
    offdiagonal(0) = 0.0; // This values is trivial, set to 0.0
    xmax = diagonal(n - 1) + fabs(offdiagonal(n - 1));
    xmin = diagonal(n - 1) - fabs(offdiagonal(n - 1));
    for (int i = n - 2; i >= 0; i--)
    {
        h = fabs(offdiagonal(i)) + fabs(offdiagonal(i + 1));
        if ((diagonal(i) + h) > xmax)
        {
            xmax = diagonal(i) + h;
        }
        if ((diagonal(i) - h) < xmin)
        {
            xmin = diagonal(i) - h;
        }
    }

    /* 
        Tolerance
    */
    double epsilon;
    epsilon = ((xmax + xmin) > 0.0) ? xmax : -xmin;
    epsilon *= DBL_EPSILON;
    if (relative_tolerance < 0.0)
    {
        relative_tolerance = epsilon;
    }
    epsilon = 0.5 * relative_tolerance + 7.0 * epsilon;

    /* 
        Innerblock of the bisecton method. See Calculation of the eigenvalues of -
         a symmetric tridiagonal matrix by the method of bisection -
         Barth, W and Marting, Rs and Wilkingson, HJ
    */
    // Lower and upper limits
    double x0, xn, xmid;
    vec xmins(n);
    xn = xmax;
    for (int i = 0; i < n; i++)
    {
        v(i) = xmax;
        xmins(i) = xmin;
    }

    double iterator = 0; // Total number of bisections

    /* 
        Find all eigenvalues from largest to smallest, storing: storing smallest to largest 
    */
    double tolerance, a;

    for (int k = n - 1; k >= 0; k--)
    {
        x0 = xmin;
        for (int i = k; i >= 0; i--)
        {
            if (x0 < xmins(i))
            {
                x0 = xmins(i);

                break;
            }
        }
        if (xn > v(k))
        {
            xn = v(k);
        }

        tolerance = 2 * DBL_EPSILON * (fabs(x0) + fabs(xn)) + relative_tolerance;

        while ((xn - x0) > tolerance)
        {
            // Bisection part of the algorithm
            xmid = (xn + x0) / 2;

            iterator += 1;
            int a = 0;

            m_sturm_sequence(diagonal, offdiagonal, xmid, n, a);

            if (a < k + 1)
            {
                if (a < 1)
                {
                    x0 = xmins(0) = xmid;
                }
                else
                {
                    x0 = xmins(a) = xmid;
                    if (v(a - 1) > xmid)
                    {
                        v(a - 1) = xmid;
                    }
                }
            }
            else
            {
                xn = xmid;
            }
            tolerance = 2 * DBL_EPSILON * (fabs(x0) + fabs(xn)) + relative_tolerance;
        }
        v(k) = (xn + x0) / ((double)2.0);
    }
    relative_tolerance = epsilon; // Upperbound of error
    n = iterator;                 // Number of bisections
}

void initialize_bi(int interact, vec &d, vec &nd, int n, double h)
{
    double hh = h * h;
    vec rho(n);

    if (interact != 0)
    {
        rho(0) = h;
        for (int i = 1; i < n; i++)
        {
            rho(i) = rho(i - 1) + h;
        }
    }
    if (interact == 0)
    {
        d.fill(2.0 / ((double)hh));
        nd.fill(-1.0 / ((double)hh));
    }
    else if (interact == 1)
    {
        for (int i = 0; i < n; i++)
        {
            d(i) = (2.0 / ((double)hh) + rho(i) * rho(i));
            nd(i) = (-1.0 / ((double)hh));
        }
    }
} // End: function initialize()

void m_sturm_sequence(vec &d, vec &b, double x, int n, int &a)
{
    /*
        Finds the number of roots in the interval of 
    */
    double q = 1.0;
    // int a = 0;
    for (int i = 0; i < n; i++)
    {
        if (q != 0.0)
        {
            q = d(i) - x - ((b(i) * b(i)) / q);
        }
        else
        {
            q = d(i) - x - (fabs(b(i) / DBL_EPSILON)); // Prevent division by 0, dividing by a small number
        }
        if (q < 0.0)
        {
            // Variation in signs
            a++;
        }
    }
    // return a;
}