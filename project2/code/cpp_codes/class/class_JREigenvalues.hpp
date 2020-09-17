#ifndef JREIGENVALUES_HPP
#define JREIGENVALUES_HPP

#include <armadillo>
#include <fstream>

using namespace arma;
using namespace std;

class JREigenvalues
{
private:
    //
protected:
    ofstream m_ofile;
    int m_N;
    double m_h;
    mat m_A;

public:
    void initialize(int, int, double);
    void write_to_file(string filename);
};

class solver : public JREigenvalues
{
private:
    void get_max(mat, double &, int &, int &, int);
    void jacobi_rotate(mat, mat, int, int, int);

public:
    void solve();
};

class unit_test : public JREigenvalues
{
private:
    void test_JacobiRotate(mat, int);
    void test_OrthogonalityPreservation(mat, mat, int);
    void test_ConservationOfEigenvalues(mat, vec, int);
    void test_LargestDiagonalElement(mat, int, int);

public: // maybe a better way of doing this?
    void test();
};
#endif

/* 
void max_Offdiagonal_element(mat, double &, int &, int &, int);
void rotate_matrix(mat, mat, int, int, int);
*/