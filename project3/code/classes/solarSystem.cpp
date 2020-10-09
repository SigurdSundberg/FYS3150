#include <iostream>

#include "solarSystem.hpp"

using namespace std;

solarsystem::solarsystem()
{
}

planet &solarsystem::createPlanet(double m, vec3 pos, vec3 vel)
{
    m_planets.push_back(planet(m, pos, vel));
    return m_planets.back();
}

solarsystem::~solarsystem()
{
}

void solarsystem::calculateForceAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;

    for (planet &current : m_planets)
    {
        current.resetForce();
    }
}

int solarsystem::numberOfPlanets() const
{
    return m_planets.size();
}

double solarsystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double solarsystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double solarsystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

void solarsystem::writeToFile(string filename)
{
    if (!m_file.good())
    {
        m_file.open(filename.c_str(), ofstream::out);
        if (!m_file.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    m_file << numberOfPlanets() << endl;
    m_file << " something will go here" << endl;
    for (planet &planet : m_planets)
    {
        m_file << "smth " << planet.position.x() << " " << planet.position.y() << " " << planet.position.z() << "\n";
    }
    m_file.close();
}