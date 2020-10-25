#include "ODEsolver.hpp"
#include <iostream>
ODEsolver::ODEsolver(double h) : m_h(h)
{
}

void ODEsolver::oneStepVelocityVerlet(solarsystem &system)
{
    /* 
    m_h is the steplength dt 
    working with vectors on the form vec3 (x,y,z)
    X.position : vec3(x,y,z)
    X.velocity : vec3(x,y,z)
    X.position : vec3(x,y,z)

    */
    int n = system.numberOfPlanets();
    std::vector<vec3> aii;
    vec3 ai;

    system.calculateAccel();
    for (planet &current : system.planets())
    {
        aii.push_back(current.accel);
        current.position = current.position + m_h * current.velocity + (m_h * m_h) / 2 * current.accel;
    }

    system.calculateAccel();
    int i = 0;
    for (planet &current : system.planets())
    {
        ai = aii[i];
        // std::cout << ai << std::endl;
        // std::cout << "Next" << std::endl;
        // std::cout << current.accel << std::endl;
        current.velocity = current.velocity + m_h / 2 * (current.accel + ai);
        i += 1;
    }
}

// void ODEsolver::oneStepVelocityVerlet(solarsystem &system, double alpha)
// {
//     /*
//     m_h is the steplength dt
//     working with vectors on the form vec3 (x,y,z)
//     X.position : vec3(x,y,z)
//     X.velocity : vec3(x,y,z)
//     X.position : vec3(x,y,z)

//     */
//     int n = system.numberOfPlanets();
//     std::vector<vec3> aii;
//     vec3 ai;

//     system.calculateAccel(alpha);
//     for (planet &current : system.planets())
//     {
//         aii.push_back(current.accel);
//         current.position = current.position + m_h * current.velocity + (m_h * m_h) / 2 * current.accel;
//     }

//     system.calculateAccel(alpha);
//     int i = 0;
//     for (planet &current : system.planets())
//     {
//         ai = aii[i];
//         // std::cout << ai << std::endl;
//         // std::cout << "Next" << std::endl;
//         // std::cout << current.accel << std::endl;
//         current.velocity = current.velocity + m_h / 2 * (current.accel + ai);
//         i += 1;
//     }
// }

void ODEsolver::oneStepForwardEuler(solarsystem &system)
{
    system.calculateAccel();
    for (planet &current : system.planets())
    {
        current.position = current.position + m_h * current.velocity;
        current.velocity = current.velocity + m_h * current.accel;
        // std::cout << current.accel << std::endl;
    }
}