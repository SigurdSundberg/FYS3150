#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include "vec3.h"
#include "solarSystem.hpp"
class ODEsolver
{
private:
    double m_h;

public:
    ODEsolver(double h);
    void oneStepVelocityVerlet(class solarsystem &);
    void oneStepVelocityVerlet(class solarsystem &, double);
    void oneStepForwardEuler(class solarsystem &);
};
#endif