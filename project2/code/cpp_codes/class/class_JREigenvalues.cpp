#include "JREigenvalues.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*
    ** n size of matrix 
    ** interact is setup of matrix
    ** 
*/
void JREigenvalues::initialize(int n, int interact, double u0, double umax)
{
    // interact = matrix to initialize
    m_N = n;
    mat m_A;
    m_u0 = u0;
    m_umax = umax;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            /* code */
        }
    }
};

void JREigenvalues::write_to_file(string filename)
{
    m_ofile << setiosflags(ios::scientific);
    m_ofile.open(filename);
    for (int i = 0; i < m_N; i++)
    {
        m_ofile << "Data goes here " << endl;
    }
    m_ofile.close();
}