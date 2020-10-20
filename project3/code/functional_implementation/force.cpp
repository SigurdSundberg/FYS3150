#include "force.hpp"

vec3 force(double mass, vec3 current, vec3 other)
{
    vec3 F, tmp;
    double r, G = ;
    tmp = current - other;
    r = tmp.lengthSquared();
    F = -mass * current * G / ((double)r * r * r);
    return F;
}
