#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "planet.hpp"
#include "solarSystem.hpp"
#include "ODEsolver.hpp"

std::ofstream ofile;

void readFile(double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int Nparticles, std::string filename);
void wtf(double value);
int main(int argc, char const *argv[])
{
    // Define constants
    double t, t_end, dt;
    t_end = 100;
    dt = 1e-7;

    double p = 0, pp = 0, ppp = 2;
    double tmp;
    double peri = 0.3075;
    int N = 1e3;

    // Setup the system and integrator
    ODEsolver integrator(dt);
    solarsystem solarsystem(2, 0);
    solarsystem.createPlanet(1, vec3(0, 0, 0), vec3(0, 0, 0));
    solarsystem.createPlanet(1.65e-07, vec3(peri, 0, 0), vec3(0, 12.44, 0));

    // Setup mercury as a planet and prints the initial position
    vec3 mercury, prevPos;
    mercury = solarsystem.planets()[1].position;
    std::cout << "Initial angle " << mercury.y() / mercury.x() << std::endl;

    while (t < t_end)
    {
        integrator.oneStepVelocityVerlet(solarsystem);
        t += dt;

        if (t > 99)
        { // Only care about the case where t gets close to a century
            mercury = solarsystem.planets()[1].position;
            p = mercury.length();
            if (p > pp && pp < ppp)
            {

                tmp = prevPos.y() / prevPos.x();
                wtf(tmp);
                std::cout << tmp << std::endl;
            }
            prevPos = mercury;
            ppp = pp;
            pp = p;
        }
    }
    return 0;
}

void wtf(double value)
{
    ofile.open("./Data/PPNR.txt", std::ios_base::app);
    ofile << std::setw(15) << value << std::endl;
    ofile.close();
}
