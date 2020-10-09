#ifndef FILE_MAN_HPP
#define FILE_MAN_HPP

#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdio>

#include "../vec3.h"

void readFile(std::string, std::string, double *, double *, double *, double *, double *, double *, double *, int);
void writeToFile(std::string, vec3, int);
#endif