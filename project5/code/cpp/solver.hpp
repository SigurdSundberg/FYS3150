/*
    ** m_u is denoted as the indivudial initial vector
    ** m_v is denoted as the given vector split later
    ** m_solution is the vector set to the solution at the end
*/

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace arma;

class solver
{
private:
    void forwardSubstitution();
    void backwardSubstitution();
    void forward2d();
    void setup(string solver);
    vec m_x, m_solution, m_v, m_u, m_b;
    mat m_U, m_V;
    double m_alpha, m_c;
    bool setupDone = false; // Potential artifact
    int m_N;
    string m_solver = "NONE";
    ofstream m_ofile;

public:
    void initialize(int n, vec u, double alpha);
    void init2d(int n, mat U, double alpha);
    void solve2d();
    void reset(); // This can be made private
    void forwardEuler();
    void backwardEuler();
    void CrankNicholson();
    string getSolver();
    void writeToFile(string path, string suffix, double t);
    void writeToFile2d(string path, string suffix, double t);
};

#endif