#include "catch.hpp"
#include "planet.hpp"
#include "solarSystem.hpp"
#include "vec3.h"
#include "ODEsolver.hpp"

TEST_CASE("Conservation VV, [base]")
{
    solarsystem s(2, 0);
    ODEsolver I(1e-6);

    double t1 = 10, t2 = 50, t3 = 200;
    double t = 0;

    s.createPlanet(1, vec3(0, 0, 0), vec3(0, 0, 0));
    s.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 2 * M_PI, 0));
    double iE = s.totalEnergy();
    double iA = s.getAngMom();
    while (t < t1)
    {
        I.oneStepVelocityVerlet(s);
        t += 1e-6;
    }
    double E1 = s.totalEnergy();
    double A1 = s.getAngMom();
    while (t < t2)
    {
        I.oneStepVelocityVerlet(s);
        t += 1e-6;
    }
    double E2 = s.totalEnergy();
    double A2 = s.getAngMom();
    while (t < t3)
    {
        I.oneStepVelocityVerlet(s);
        t += 1e-6;
    }
    double E3 = s.totalEnergy();
    double A3 = s.getAngMom();

    double E = 1e-7;
    REQUIRE(abs(iE - E1) < E);
    REQUIRE(abs(iE - E2) < E);
    REQUIRE(abs(iE - E3) < E);
    REQUIRE(abs(iA - A1) < E);
    REQUIRE(abs(iA - A2) < E);
    REQUIRE(abs(iA - A3) < E);
}

TEST_CASE("Conservation FE, [base]")
{
    solarsystem s(2, 0);
    ODEsolver I(1e-6);

    double t1 = 10, t2 = 50, t3 = 200;
    double t = 0;

    s.createPlanet(1, vec3(0, 0, 0), vec3(0, 0, 0));
    s.createPlanet(3e-6, vec3(1, 0, 0), vec3(0, 2 * M_PI, 0));
    double iE = s.totalEnergy();
    double iA = s.getAngMom();
    while (t < t1)
    {
        I.oneStepForwardEuler(s);
        t += 1e-6;
    }
    double E1 = s.totalEnergy();
    double A1 = s.getAngMom();
    while (t < t2)
    {
        I.oneStepForwardEuler(s);
        t += 1e-6;
    }
    double E2 = s.totalEnergy();
    double A2 = s.getAngMom();
    while (t < t3)
    {
        I.oneStepForwardEuler(s);
        t += 1e-6;
    }
    double E3 = s.totalEnergy();
    double A3 = s.getAngMom();

    double E = 1e-4;
    REQUIRE(abs(iE - E1) < E);
    REQUIRE(abs(iE - E2) < E);
    REQUIRE(abs(iE - E3) < E);
    REQUIRE(abs(iA - A1) < E);
    REQUIRE(abs(iA - A2) < E);
    REQUIRE(abs(iA - A3) < E);
}
