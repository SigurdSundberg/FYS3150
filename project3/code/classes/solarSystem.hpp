#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <vector>
#include <fstream>
#include <string>

#include "planet.hpp"

class solarsystem
{
private:
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    std::vector<planet> m_planets;

public:
    solarsystem();
    planet &createPlanet(double mass, vec3 position, vec3 velocity);
    ~solarsystem();
    void calculateForceAndEnergy();
    int numberOfPlanets() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(std::string filename);
};

#endif