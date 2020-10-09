#ifndef PLANET_HPP
#define PLANET_HPP

#include "../vec3.h"

class planet
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force; // Forces acting the x,y,z directions
    double mass;

    planet(double mass, vec3 position, vec3 velocity);
    planet(double mass, double x, double y, double z, double vx, double vy, double vz);
    ~planet();

    void resetForce();
};

#endif
