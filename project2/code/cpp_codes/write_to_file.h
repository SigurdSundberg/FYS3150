/*
Header for writing to file functions 
*/

#include <armadillo>
#include <string>

void write_to_file_data(std::string, arma::vec, arma::mat);
void write_to_file_time(std::string, double, double, int);
void write_to_file_iterations(std::string, int, int);