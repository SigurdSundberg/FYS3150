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

double planet::getKinetic()
{
    return 0.5 * mass * velocity.lengthSquared();
}

vec3 planet::getAngularMomentum()
{
    return position.cross(velocity) * mass;
}

void planet::resetAcceleration()
{
    accel.zeros();
}

vec3 planet::getForce()
{
    return accel * mass;
}
