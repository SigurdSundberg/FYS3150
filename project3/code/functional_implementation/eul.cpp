#include "eul.hpp"

void oneStepEuler(vec3 &pos, vec3 &vel, double h, vec3 force, double m)
{
    vec3 a;
    a = force / m;
    pos = pos + h * vel;
    vel = vel + h * a;
}