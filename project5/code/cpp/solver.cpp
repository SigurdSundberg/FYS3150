#include "solver.hpp"

/*
    * alpha = dt/dx/dx // Always positive
*/
void solver::initialize(int n, vec u, double alpha)
{
    m_N = n;
    m_v = vec(m_N);
    m_solution = vec(m_N);
    m_b = vec(m_N);
    m_u = vec(m_N);

    m_v = u;
    m_u = u;
    m_solution = m_u; // Sets the solution vector so it can be written to file

    m_alpha = alpha;
}

void solver::setup(string solver)
{
    double m_aa = m_alpha * m_alpha;
    if (solver == "BE")
    {
        for (int i = 0; i < m_N; i++)
        {
            m_b(i) = 1 + 2 * m_alpha; // Backward Euler
        }
        for (int i = 1; i < m_N; i++)
        {
            m_b(i) -= m_aa / m_b(i - 1);
        }
        // m_b(0) = 1;
        // m_b(m_N - 1) = 1;
        setupDone = true; // Potential artifact
    }
    else if (solver == "CN")
    {
        for (int i = 0; i < m_N; i++)
        {
            m_b(i) = 2 + 2 * m_alpha;
        }
        for (int i = 1; i < m_N; i++)
        {
            m_b(i) -= m_aa / m_b(i - 1);
        }
        // m_b(0) = 1;
        // m_b(m_N - 1) = 1;
        m_c = (2 - 2 * m_alpha);
        setupDone = true; // Potential artifact
    }
    else if (solver == "FE")
    {
        m_c = (1 - 2 * m_alpha);
        setupDone = true; // Potential artifact
    }
    else if (solver == "2D")
    {
        m_c = m_alpha;
        setupDone = true;
    }
    else
    {
        cout << "No valid solver was setup." << endl;
    }
}

void solver::reset()
{
    if (m_solver == "2D")
    {
        m_U = m_V;
        setupDone = false;
    }
    else
    {
        m_u = m_v;
        setupDone = false; // Potential artifact
    }
}

void solver::writeToFile(string path, string suffix, double t)
{
    if (m_solver == "NONE")
    {
        m_solver = "INITIAL";
    }
    string outfile;
    outfile = path + m_solver + suffix;
    m_ofile.open(outfile, ios_base::app);
    // string format = "Temperature Datapoints Solution Vector";
    // m_ofile << format << endl;
    m_ofile << "time=" << t << endl;
    m_ofile << "datapoints=" << m_N << endl;
    for (int i = 0; i < m_N; i++)
    {
        m_ofile << setprecision(15) << m_solution(i) << endl;
    }
    m_ofile.close();
}

void solver::forwardEuler()
{
    if (m_solver != "FE")
    {
        // Checks if alpha is too large to prevent overflows and potential crashes for the Forward scheme
        if (m_alpha > 0.5)
        {
            cerr << "Alpha is too large for the scheme to be stable. alpha = " << m_alpha << " Aborting..." << endl;
            terminate();
        }
        m_solver = "FE";
        reset();
        setup(m_solver);
    }
    forwardSubstitution();
    m_solution = m_u;
}

void solver::backwardEuler()
{
    if (m_solver != "BE")
    {
        m_solver = "BE";
        reset();
        setup(m_solver);
    }
    backwardSubstitution();
    m_u = m_solution;
}

void solver::CrankNicholson()
{
    if (m_solver != "CN")
    {
        m_solver = "CN";
        reset();
        setup(m_solver);
    }
    forwardSubstitution();
    backwardSubstitution();
    m_u = m_solution; // Update the m_u vector to the solution vector as m_u is used as base for the calculations
}
string solver::getSolver()
{
    return m_solver;
}

/*
    * This is implemented correctly and should work
    * we update m_u
*/
void solver::forwardSubstitution()
{
    vec unew = zeros<vec>(m_N);
    for (int i = 1; i < m_N - 1; i++)
    {
        unew(i) = m_c * m_u(i) + m_alpha * (m_u(i - 1) + m_u(i + 1));
    }
    m_u = unew;
}

/* 
    * Works
    * 

*/
void solver::backwardSubstitution()
{
    double m_a = -m_alpha;
    double aa = m_alpha * m_alpha;
    for (int i = 1; i < m_N - 1; i++)
    {
        // m_b(i) -= aa / (double)m_b(i - 1);
        m_u(i) -= m_a * m_u(i - 1) / (double)m_b(i - 1);
    }
    m_solution(m_N - 2) = m_u(m_N - 2) / m_b(m_N - 2);
    for (int i = m_N - 3; i > 0; i--)
    {
        m_solution(i) = (m_u(i) - m_a * m_solution(i + 1)) / m_b(i);
    }
}

void solver::init2d(int n, mat U, double alpha)
{
    m_N = n;
    m_V = mat(m_N, m_N);
    m_U = mat(m_N, m_N);

    m_V = U;
    m_U = U;

    m_alpha = alpha;
}

void solver::solve2d()
{
    if (m_solver != "2D")
    {
        // Checks if alpha is too large to prevent overflows and potential crashes for the Forward scheme
        if (m_alpha > 0.25)
        {
            cerr << "Alpha is too large for the scheme to be stable. alpha = " << m_alpha << " Aborting..." << endl;
            terminate();
        }
        m_solver = "2D";
        reset();
        setup(m_solver);
    }
    forward2d();
}

void solver::forward2d()
{ // row col
    mat Unew = zeros<mat>(m_N, m_N);
    for (int i = 1; i < m_N - 1; i++)
    {
        for (int j = 1; j < m_N - 1; j++)
        {
            Unew(i, j) = m_U(i, j) + m_c * (m_U(i + 1, j) + m_U(i - 1, j) + m_U(i, j + 1) + m_U(i, j - 1) - 4 * m_U(i, j));
        }
    }
    /* 
        * As we have chosen a problem where the edges are the same,
        * no flux or zero boundary conditions
        * this updates the edges such that they stay the same each time
    */
    for (int i = 1; i < m_N - 1; i++)
    {
        Unew(i, 0) = m_U(i, 0) + m_c * (m_U(i + 1, 0) + m_U(i - 1, 0) + m_U(i, 1) + -3 * m_U(i, 0));
        Unew(i, m_N - 1) = m_U(i, m_N - 1) + m_c * (m_U(i + 1, m_N - 1) + m_U(i - 1, m_N - 1) + m_U(i, m_N - 2) - 3 * m_U(i, m_N - 1));
    }
    m_U = Unew;
}

void solver::writeToFile2d(string path, string suffix, double t)
{
    if (m_solver == "NONE")
    {
        m_solver = "INITIAL2D";
    }
    string outfile;
    outfile = path + m_solver + suffix;
    m_ofile.open(outfile, ios_base::app);
    m_ofile << "time=" << t << endl;
    m_ofile << "datapoints=" << m_N << "x" << m_N << endl;
    for (int i = 0; i < m_N; i++)
    {
        for (int j = 0; j < m_N; j++)
        {
            m_ofile << setprecision(15) << setw(25) << m_U(i, j);
        }
        m_ofile << endl;
    }
    m_ofile.close();
}