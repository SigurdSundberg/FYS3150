#include <iostream>

#include "solarSystem.hpp"

using namespace std;

solarsystem::solarsystem() : m_kineticEnergy(0),
                             m_potentialEnergy(0)
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

void solarsystem::calculateAccel()
{
    for (planet &current : m_planets)
    {
        current.resetAcceleration();
    }

    for (planet &current : m_planets)
    {
        for (planet &other : m_planets)
        {
            vec3 deltaR = current.position - other.position;
            double r = deltaR.length();
            if (r != 0)
            {
                double coeff = -G * other.mass / ((double)r * r * r);
                current.accel += coeff * deltaR;
                // cout << r << endl;
            }
        }
    }
}

void solarsystem::calculateAccel(double alpha)
{
    for (planet &current : m_planets)
    {
        current.resetAcceleration();
    }

    for (planet &current : m_planets)
    {
        for (planet &other : m_planets)
        {
            vec3 deltaR = current.position - other.position;
            double r = deltaR.length();
            if (r != 0)
            {
                double coeff = -G * other.mass / ((double)pow(r, alpha) * r);
                current.accel += coeff * deltaR;
                // cout << deltaR << endl;
            }
        }
    }
}

std::vector<planet> &solarsystem::planets()
{
    return m_planets;
}

int solarsystem::numberOfPlanets() const
{
    return m_planets.size();
}

double solarsystem::totalEnergy()
{
    m_kineticEnergy = getKinetic();
    m_potentialEnergy = getPotential();
    return m_kineticEnergy + m_potentialEnergy;
}

double solarsystem::getKinetic()
{
    for (planet &planet : m_planets)
    {
        m_kineticEnergy += planet.getKinetic();
    }
    return m_kineticEnergy;
}

double solarsystem::getPotential() // Figure out how to do this bad boy
{
    m_potentialEnergy = 0;
    for (int i = 0; i < numberOfPlanets(); i++)
    {
        planet &current = m_planets[i];
        for (int j = i + 1; j < numberOfPlanets(); j++)
        {
            planet &other = m_planets[j];
            vec3 deltaR = current.position - other.position;
            double r = deltaR.length();
            m_potentialEnergy -= G * current.mass * other.mass / r;
        }
    }

    // for (planet &current : m_planets)
    // {
    //     for (planet &other : m_planets)
    //     {
    //         vec3 deltaR = current.position - other.position;
    //         double r = deltaR.length();
    //         if (r != 0)
    //         {
    //             m_potentialEnergy -= G * current.mass * other.mass / r;
    //         }
    //     }
    // }
    return m_potentialEnergy;
}

void solarsystem::initializeDataFile(string filename)
{
    if (m_file.good())
    {
        m_file.open(filename.c_str(), std::ofstream::trunc);
        if (!m_file.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    m_file << numberOfPlanets() << endl;
    m_file << "id x y z" << endl;
}

void solarsystem::writeToFilePos(string filename)
{
    if (!m_file.good())
    {
        m_file.open(filename.c_str(), std::ios_base::app);
        if (!m_file.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    int i = 1;
    for (planet &planet : m_planets)
    {
        m_file << i << " "
               << " " << planet.position.x() << " " << planet.position.y() << " " << planet.position.z() << std::endl;
        i += 1;
    }
    m_file.close();
}

void solarsystem::writeToFileEnergy(string filename)
{
    double K, U, T;
    K = getKinetic();
    U = getPotential();
    T = U + K;
    m_file.open("./Data/" + filename, ios_base::app);
    m_file << setw(10) << K << setw(10) << U << setw(10) << T << endl;
    m_file.close();
}
