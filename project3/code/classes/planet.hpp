#ifndef PLANET_HPP
#define PLANET_HPP
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

class planet
{
private:
    double mass;
    double energy_potential;
    double energy_kinetic;

public:
    planet();
    planet(double M, std::vector<double> pos, std::vector<double> vel);
    planet(double M, double x, double y, double z, double vx, double vy, double vz);
    ~planet();
};

#endif
