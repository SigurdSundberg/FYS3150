#ifndef PLANET_HPP
#define PLANET_HPP

#include "vec3.h"

class planet
{
private:
    vec3 force;

public:
    vec3 position;
    vec3 velocity;
    vec3 accel; // Forces acting the x,y,z directions
    double mass;

    planet(double mass, vec3 position, vec3 velocity);
    planet(double mass, double x, double y, double z, double vx, double vy, double vz);
    double getKinetic();
    void resetAcceleration();
    vec3 getForce();
};

#endif
