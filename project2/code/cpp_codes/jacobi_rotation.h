/* 
Header file to declare functions
*/
#include <armadillo>

void initialize(int, arma::mat &, arma::mat &, int, double);
void find_max_element(arma::mat, int, double &, int &, int &);
void rotate_matrix(arma::mat &, arma::mat &, int, int, int);
void write_to_file(std::string, arma::vec);

/* // Using catch2 to test my functions
void test_OrthogonalityPreservation(mat, mat, int);
void test_ConservationOfEigenvalues(mat, vec, int);
void test_JacobiRotate(mat, int);
void test_Largest_diagonal_element(mat, int, int);
*/