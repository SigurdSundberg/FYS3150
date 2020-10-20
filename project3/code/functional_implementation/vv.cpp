#include "vv.hpp"

void oneStepVV(double mass, vec3 &pos, vec3 &vel, double h)
{
    vec3 aii, ai;
    double r, rrr;
    r = pos.length();
    vec3 forcei;
    vec3 force;

    ai = force / mass;
    pos = pos + h * vel + h / 2 * ai;
    aii = forcei / mass;
    vel = vel + h / 2 * (aii + ai);
}