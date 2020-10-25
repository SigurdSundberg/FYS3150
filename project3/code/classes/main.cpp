#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "planet.hpp"
#include "solarSystem.hpp"
#include "ODEsolver.hpp"

void readFile(double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int Nparticles, std::string filename);
int main(int argc, char const *argv[])
{
    double t, t_end, dt;
    std::string filename, filename_;
    filename = "./Data/";
    int Nparticles = 10, Problem;

    if (argv[1] == "two")
    {
        Problem = 2;
    }
    if (argv[1] == "three")
    {
        Problem = 3;
    }
    if (argv[1] == "solar")
    {
        Problem = 10;
    }
    double *x, *y, *z, *vx, *vy, *vz; //To store initial conditions for each particle.
    double *mass;                     //Store mass of particles.
    x = new double[Nparticles];
    y = new double[Nparticles];
    z = new double[Nparticles];
    vx = new double[Nparticles];
    vy = new double[Nparticles];
    vz = new double[Nparticles];
    mass = new double[Nparticles];

    if (Problem == 2)
    {

        t_end = 100;
        dt = 0.0001;
        t = 0.0;
        int i = 0;
        solarsystem solarsystem(2, 0);
        readFile(x, y, z, vx, vy, vz, mass, 10, "initial.txt");
        solarsystem.createPlanet(mass[0], vec3(x[0], y[0], z[0]), vec3(vx[0], vy[0], vz[0]));
        solarsystem.createPlanet(mass[3], vec3(x[3], y[3], z[3]), vec3(vx[3], vy[3], vz[3]));

        filename_ = filename + "V2" + ".xyz";
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
    if (Problem == 3)
    {
        t_end = 10;
        t = 0.0;
        dt = 0.0001;
        int i = 0;
        readFile(x, y, z, vx, vy, vz, mass, 10, "bari");
        solarsystem solarsystem(2, 0);
        t = 0.0;
        solarsystem.createPlanet(mass[0], vec3(x[0], y[0], z[0]), vec3(vx[0], vy[0], vz[0]));
        solarsystem.createPlanet(mass[3], vec3(x[3], y[3], z[3]), vec3(vx[3], vy[3], vz[3])); // Earth
        solarsystem.createPlanet(mass[5], vec3(x[5], y[5], z[5]), vec3(vx[5], vy[5], vz[5])); // Jupiter

        filename_ = filename + "V3.xyz";
        solarsystem.initializeDataFile(filename_);
        ODEsolver integrator(dt);
        std::cout << "Total energy before " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
        std::cout << "Angular momentum before " << solarsystem.getAngMom() << std::endl;
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
        std::cout << "Angular momentum after " << solarsystem.getAngMom() << std::endl;
    }
    if (Problem == 10)
    {
        // Setup constant
        t_end = 200;
        t = 0.0;
        dt = 0.0001;
        int i = 0;

        solarsystem solarsystem(2, 0);
        readFile(x, y, z, vx, vy, vz, mass, 10, "bari");
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

        // Setup files and integrator
        filename_ = filename + "V10" + ".xyz";
        solarsystem.initializeDataFile(filename_);
        ODEsolver integrator(dt);
        // Print initial energy
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
        // Print final energy
        std::cout << "Total energy after " << solarsystem.totalEnergy() << std::endl;
        std::cout << solarsystem.getKinetic() << " " << solarsystem.getPotential() << std::endl;
    }

    return 0;
}

void readFile(double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int Nparticles, std::string filename)
{
    // Credit FYS3150 teachers.
    const char *filename_pos_and_vel;
    if (filename == "bari")
    {
        filename_pos_and_vel = "./Input/initialBary.txt";
    }
    else
    {
        filename_pos_and_vel = "./Input/initial.txt"; //Each line of file gives initial condition for a particle on the form: x y z vx vy vz
    }
    const char *filename_mass = "./Input/masses.txt"; //Each line of the file contains a mass for a given particle.

    //Open files
    FILE *fp_init = fopen(filename_pos_and_vel, "r"); //Open file to read, specified by "r".
    FILE *fp_mass = fopen(filename_mass, "r");        //Open file to read.

    //Loop over each particle and extract its mass and initial conditions:
    for (int i = 0; i < Nparticles; i++)
    {
        int _ = fscanf(fp_init, "%lf %lf %lf %lf %lf %lf", &x[i], &y[i], &z[i], &vx[i], &vy[i], &vz[i]); // One %lf (lf=long float or double) for each floating point number on each line of the file.
        _ = fscanf(fp_mass, "%lf", &mass[i]);                                                            //Extract mass for particle i.
    }

    fclose(fp_init); //Close file with initial conditions
    fclose(fp_mass); //Close file with masses.
}
