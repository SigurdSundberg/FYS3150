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
    double c = 63239.7263;
    double cc = c * c;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double m_angularMomentum;
    double m_alpha;
    double m_l = 0;
    double m_type;
    std::vector<planet> m_planets;

public:
    solarsystem(double, double);
    planet &createPlanet(double mass, vec3 position, vec3 velocity);
    ~solarsystem();
    void calculateAccel();
    // void calculateAccel(double);
    std::vector<planet> &planets();

    double totalEnergy();
    int numberOfPlanets() const;
    double getPotential();
    double getKinetic();
    double getAngMom();
    void initializeDataFile(std::string filename);
    void writeToFilePos(std::string filename);
    void writeToFileEnergy(std::string filename);
};

#endif