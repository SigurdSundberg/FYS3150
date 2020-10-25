#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "planet.hpp"
#include "solarSystem.hpp"
#include "ODEsolver.hpp"

void write_to_file(std::string, double, double);
std::ofstream ofile;
// This is the code for varying beta.
int main(int argc, char const *argv[])
{
    double t = 0.0, t_end = 300, dt = 1e-5;
    std::string filename, filename_;
    filename = "./Data/AlphaElip/";
    double k = 2.8;
    for (int j = 0; j < 6; j++)
    { // 2.9 and 2.95
        t = 0.0;
        std::cout << j << std::endl;
        int i = 0;
        solarsystem solarsystem(k, 0);
        solarsystem.createPlanet(1.0, vec3(0, 0, 0), vec3(0, 0, 0));
        solarsystem.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 5, 0)); // 5 2 * M_PI
        filename_ = filename + "Plot" + std::to_string(j) + "Elip.xyz";
        ODEsolver integrator(dt);
        while (t < t_end)
        {
            integrator.oneStepVelocityVerlet(solarsystem);
            t += dt;
            i += 1;
            if (i % 1000 == 0)
            {
                std::vector<planet> system = solarsystem.planets();
                planet &earth = system[1];
                double r = earth.position.length();
                write_to_file(filename_, t, r);
            }
        }
        k += 0.05;
    }
    return 0;
}

void write_to_file(std::string filename, double t, double r)
{
    ofile.open(filename, std::ios_base::app);
    ofile << std::setw(10) << t << std::setw(20) << r << std::endl;
    ofile.close();
}
