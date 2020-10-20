#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "planet.hpp"

class solarsystem
{
private:
    double G = 4 * M_PI * M_PI;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    std::vector<planet> m_planets;

public:
    solarsystem();
    planet &createPlanet(double mass, vec3 position, vec3 velocity);
    ~solarsystem();
    void calculateAccel();
    void calculateAccel(double);
    std::vector<planet> &planets();

    double totalEnergy();
    int numberOfPlanets() const;
    double getPotential();
    double getKinetic();
    void initializeDataFile(std::string filename);
    void writeToFilePos(std::string filename);
    void writeToFileEnergy(std::string filename);
};

#endif