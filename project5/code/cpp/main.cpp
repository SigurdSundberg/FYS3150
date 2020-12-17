
#include "solver.hpp"

inline double f(double x)
{
    return -((double)x);
}

int main(int argc, char const *argv[])
{
    double dt, alpha, xmin, xmax, t, tFinal;
    double dx; // dx = dy
    int n;
    vec u;
    mat U;
    string path, sx, ss; // sx = suffix, ss = selected solver

    // Reading data from the command line
    /*
        * Absolute reads:
        *   [filepath] [filenameSuffix] [1d/2d] [dt] [dx] [xmin] [xmax] [tFinal]
    */

    path = argv[1];
    sx = argv[2];
    ss = argv[3];
    dt = atof(argv[4]);
    dx = atof(argv[5]);
    xmin = atof(argv[6]);
    xmax = atof(argv[7]);
    tFinal = atof(argv[8]);
    // path = "./data/"; // Command line arg
    // sx = "001";       // Command line arg
    // dx = 0.01;        // Command line arg
    // xmin = 0;         // Command line arg
    // xmax = 1;         // Command line arg
    // tFinal = 1;       // Command line arg
    // ss = "";          // Command line arg
    // dt = -1;          // Command lien arg

    // Defining constants
    n = (xmax - xmin) / (double)(dx) + 1; // dx = dy

    // Setup the initial function
    u = vec(n);
    for (int i = 0; i < n; i++)
    {
        u(i) = f(dx * i);
    }
    u(0) = u(n - 1) = 0;

    // Initilization of the solver
    solver Solver;
    if (ss == "1d")
    {
        alpha = 0.5; // This is the highest value of alpha for a stable FTCS
        dt = alpha * dx * dx;
        Solver.initialize(n, u, alpha);
        t = 0;
        // Solver.writeToFile(path, sx, t);
        for (t = dt; t <= tFinal; t += dt)
        {
            Solver.forwardEuler();
            // Solver.writeToFile(path, sx, t);
        }
        Solver.writeToFile(path, sx + "FINAL", t);

        for (t = dt; t <= tFinal; t += dt)
        {
            Solver.backwardEuler();
            // Solver.writeToFile(path, sx, t);
        }
        Solver.writeToFile(path, sx + "FINAL", t);

        for (t = dt; t <= tFinal; t += dt)
        {
            Solver.CrankNicholson();
            // Solver.writeToFile(path, sx, t);
        }
        Solver.writeToFile(path, sx + "FINAL", t);
    }
    else if (ss == "2d")
    {
        // Setup U
        U = zeros<mat>(n, n);
        for (int i = 0; i < n; i++)
        {
            U.col(i) = u;
        }
        path = path + "2D/";

        if (dt == -1)
        {
            alpha = 0.25; // This is the highest value of alpha for a stable FTCS
            dt = alpha * dx * dx;
        }
        else
        {
            alpha = dt / dx / dx;
        }

        Solver.init2d(n, U, alpha);
        t = 0;
        Solver.writeToFile2d(path, sx, t);
        for (t = dt; t <= tFinal; t += dt)
        {
            Solver.solve2d();
        }
        // Only writing for the final time as we are using matrices so save memory in files
        Solver.writeToFile2d(path, sx + "FINAL", t);
    }
    else
    {
        cout << "No solver chosen" << endl;
        terminate();
    }

    return 0;
}
