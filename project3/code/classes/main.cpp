#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include "planet.hpp"
#include "solarSystem.hpp"
#include "ODEsolver.hpp"

void readFile(double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int Nparticles);

int main(int argc, char const *argv[])
{
    double t, t_end, dt;
    std::string filename, filename_;
    filename = "./Data/";
    int Nparticles;

    // if (argv[1] == "two")
    // {
    //     Nparticles = 2;
    // }
    // if (argv[1] == "three")
    // {
    //     Nparticles = 3;
    // }
    // if (argv[1] == "solar")
    // {
    //     Nparticles = 10;
    // }
    Nparticles = 10;
    double *x, *y, *z, *vx, *vy, *vz; //To store initial conditions for each particle.
    double *mass;                     //Store mass of particles.
    x = new double[Nparticles];
    y = new double[Nparticles];
    z = new double[Nparticles];
    vx = new double[Nparticles];
    vy = new double[Nparticles];
    vz = new double[Nparticles];
    mass = new double[Nparticles];
    readFile(x, y, z, vx, vy, vz, mass, Nparticles);

    if (Nparticles == 2)
    {
        t_end = 10;
        dt = 0.0001;
        t = 0.0;
        int i = 0;
        solarsystem solarsystem;
        // solarsystem.createPlanet(1.0, vec3(0, 0, 0), vec3(0, 0, 0)); // Sun
        // solarsystem.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 2 * M_PI, 0)); // Earth
        solarsystem.createPlanet(mass[0], vec3(x[0], y[0], z[0]), vec3(vx[0], vy[0], vz[0]));
        solarsystem.createPlanet(mass[1], vec3(x[1], y[1], z[1]), vec3(vx[1], vy[1], vz[1]));

        filename_ = filename + "V1" + ".xyz";
        // solarsystem.initializeDataFile(filename_);
        ODEsolver integrator(dt);
        std::cout << "Total energy before " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
        while (t < t_end)
        {
            integrator.oneStepVelocityVerlet(solarsystem);
            t += dt;
            i += 1;
            if (i % 10 == 0)
            {
                // solarsystem.writeToFilePos(filename_); // Write only the final position of each time step.}
            }
        }
        std::cout << "Total energy after " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
    }
    if (Nparticles == 3)
    {
        t_end = 10;
        t = 0.0;
        dt = 0.0001;
        int i = 0;
        solarsystem solarsystem;
        // solarsystem.createPlanet(1.0, vec3(0, 0, 0), vec3(0, 0, 0)); // Sun
        // solarsystem.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 2 * M_PI, 0)); // Earth
        // solarsystem.createPlanet(1, vec3(1, 1, 1), vec3(1, 1, 1));           // Jupiter
        solarsystem.createPlanet(mass[0], vec3(x[0], y[0], z[0]), vec3(vx[0], vy[0], vz[0]));
        solarsystem.createPlanet(mass[1], vec3(x[1], y[1], z[1]), vec3(vx[1], vy[1], vz[1]));
        solarsystem.createPlanet(mass[2], vec3(x[2], y[2], z[2]), vec3(vx[2], vy[2], vz[2]));

        filename_ = filename + "V3" + ".xyz";
        solarsystem.initializeDataFile(filename_);
        ODEsolver integrator(dt);
        std::cout << "Total energy before " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
        while (t < t_end)
        {
            integrator.oneStepVelocityVerlet(solarsystem);
            t += dt;
            i += 1;
            if (i % 10 == 0)
            {
                solarsystem.writeToFilePos(filename_); // Write only the final position of each time step.}
            }
        }
        std::cout << "Total energy after " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
    }
    if (Nparticles == 10)
    {
        t_end = 100;
        t = 0.0;
        dt = 0.0001;
        int i = 0;
        solarsystem solarsystem;
        // solarsystem.createPlanet(1.0, vec3(0, 0, 0), vec3(0, 0, 0)); // Sun
        // solarsystem.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 2 * M_PI, 0)); // Earth
        // solarsystem.createPlanet(1, vec3(1, 1, 1), vec3(1, 1, 1));           // Jupiter
        solarsystem.createPlanet(mass[0], vec3(x[0], y[0], z[0]), vec3(vx[0], vy[0], vz[0]));
        solarsystem.createPlanet(mass[1], vec3(x[1], y[1], z[1]), vec3(vx[1], vy[1], vz[1]));
        solarsystem.createPlanet(mass[2], vec3(x[2], y[2], z[2]), vec3(vx[2], vy[2], vz[2]));
        solarsystem.createPlanet(mass[3], vec3(x[3], y[3], z[3]), vec3(vx[3], vy[3], vz[3]));
        solarsystem.createPlanet(mass[4], vec3(x[4], y[4], z[4]), vec3(vx[4], vy[4], vz[4]));
        solarsystem.createPlanet(mass[5], vec3(x[5], y[5], z[5]), vec3(vx[5], vy[5], vz[5]));
        solarsystem.createPlanet(mass[6], vec3(x[6], y[6], z[6]), vec3(vx[6], vy[6], vz[6]));
        solarsystem.createPlanet(mass[7], vec3(x[7], y[7], z[7]), vec3(vx[7], vy[7], vz[7]));
        solarsystem.createPlanet(mass[8], vec3(x[8], y[8], z[8]), vec3(vx[8], vy[8], vz[8]));
        solarsystem.createPlanet(mass[9], vec3(x[9], y[9], z[9]), vec3(vx[9], vy[9], vz[9]));

        filename_ = filename + "V10" + ".xyz";
        solarsystem.initializeDataFile(filename_);
        ODEsolver integrator(dt);
        std::cout << "Total energy before " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
        while (t < t_end)
        {
            integrator.oneStepVelocityVerlet(solarsystem);
            t += dt;
            i += 1;
            if (i % 50 == 0)
            {
                solarsystem.writeToFilePos(filename_); // Write only the final position of each time step.}
            }
        }
        std::cout << "Total energy after " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
    }
    return 0;
}

void readFile(double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int Nparticles)
{
    // double *x, *y, *z, *vx, *vy, *vz; //To store initial conditions for each particle.
    // double *mass; //Store mass of particles.
    // int Nparticles = 3;
    // x = new double[Nparticles];
    // y = new double[Nparticles];
    // z = new double[Nparticles];
    // vx = new double[Nparticles];
    // vy = new double[Nparticles];
    // vz = new double[Nparticles];
    // mass = new double[Nparticles];
    char *filename_pos_and_vel = "./Input/initial.txt"; //Each line of file gives initial condition for a particle on the form: x y z vx vy vz
    char *filename_mass = "./Input/masses.txt";         //Each line of the file contains a mass for a given particle.

    //Open files
    FILE *fp_init = fopen(filename_pos_and_vel, "r"); //Open file to read, specified by "r".
    FILE *fp_mass = fopen(filename_mass, "r");        //Open file to read.

    //Loop over each particle and extract its mass and initial conditions:
    for (int i = 0; i < Nparticles; i++)
    {
        fscanf(fp_init, "%lf %lf %lf %lf %lf %lf", &x[i], &y[i], &z[i], &vx[i], &vy[i], &vz[i]); // One %lf (lf=long float or double) for each floating point number on each line of the file.
        fscanf(fp_mass, "%lf", &mass[i]);                                                        //Extract mass for particle i.
    }

    fclose(fp_init); //Close file with initial conditions
    fclose(fp_mass); //Close file with masses.
}