#include "planet.hpp"

planet::planet(double m, vec3 pos, vec3 vel)
{
    mass = m;
    position = pos;
    velocity = vel;
}

planet::planet(double m, double x, double y, double z, double vx, double vy, double vz)
{
    mass = m;
    position = vec3(x, y, z);
    velocity = vec3(vx, vy, vz);
}

planet::~planet()
{
    delete[] & position, &velocity;
}

void planet::resetForce()
{
    force.zeros();
}
