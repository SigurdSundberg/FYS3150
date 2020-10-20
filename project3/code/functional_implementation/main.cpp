#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "vv.hpp"
#include "eul.hpp"
#include "../vec3.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int number_of_objects, n;
    double mass_S, mass_E, finaltime, timeStep;

    finaltime = 100;
    number_of_objects = 2;
    n = 10000;

    timeStep = finaltime / ((double)n);

    // Sun
    vec3 pos_S(0, 0, 0);
    vec3 vel_S(0, 0, 0);
    vec3 force_S(0, 0, 0);
    mass_S = 1.;

    // Earth
    vec3 pos_E(1, 0, 0);
    vec3 vel_E(6.3, 0, 0);
    vec3 force_E(0, 0, 0);
    mass_E = 0.00003;

    for (int time = 0; time < finaltime; time++)
    {
        for (int i = 0; i < number_of_objects; i++)
        {
            force_E.zeros();
            force_S.zeros();

                        /*
            Grab elements from System and turn them into vec3 
            Calculate the force between objects 
            */
        }
    }

    return 0;
}
