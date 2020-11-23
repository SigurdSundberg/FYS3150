/*
We will study the ising model, setting boltzman constant to 1 and J = 1.

To narrow down area to work with. We change temperature and then burn in before we 
start sampeling new range.
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>
#include <chrono>

#include "lib.h"

using namespace std;

ofstream ofile;
ofstream energyProbabilityFile;

inline int periodic(int i, int dim, int pos)
{
    return (i + dim + pos) % (dim);
}

void initialize(int, int **, double &, double &, int);
void MonteCarloMetropolis(int, int, int **, double, double *, double *, int);
void getEnergyAndMagneticMoment(int, int **, double &, double &);
void equil(int **, int, int, double *);
void output(int, int, double, double *);       // Output for the final expectation values after a time cycles
void output2(int, int, double, double *, int); // Output for the study of equilibration
void output3(int, double);                     // Output for the energy distribution
void outputTime(double);                       // Output for the timing runs

int main(int argc, char const *argv[])
{
    int dim;
    int MCs;
    int order;

    double T_initial, T_final, T_step, E, M; // Initial values used

    double w[17], expectation[6];

    string filename = argv[1];
    dim = atoi(argv[2]);
    MCs = atoi(argv[3]);
    order = atoi(argv[4]);
    T_initial = atof(argv[5]);
    T_final = atof(argv[6]);
    T_step = atof(argv[7]);

    filename += argv[2];
    cout << filename << endl;

    int **spinMatrix;
    spinMatrix = new int *[dim];
    for (int i = 0; i < dim; i++)
    {
        spinMatrix[i] = new int[dim];
    }

    // auto start = chrono::high_resolution_clock::now();

    ofile.open(filename, ios_base::app);
    for (double T = T_initial; T <= T_final; T += T_step)
    {
        // Resetting E and M
        E = 0.;
        M = 0.;

        // Setup possible energy values
        for (int dE = -8; dE <= 8; dE++)
        {
            w[dE + 8] = 0;
        }
        for (int dE = -8; dE <= 8; dE += 4)
        {
            w[dE + 8] = exp(-dE / ((double)T));
        }

        // Init expectation
        for (int i = 0; i < 6; i++)
        {
            expectation[i] = 0.;
        }

        // Perform the Metropolis algorithm.
        MonteCarloMetropolis(dim, MCs, spinMatrix, T, w, expectation, order);
    }
    // Use for writing timing to file, uncomment if doing timing runs
    // string tFilename = filename;
    // auto finish = chrono::high_resolution_clock::now();
    // double time = chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9);
    // outputTime(time);

    // Free memory
    for (int i = 0; i < dim; i++)
    {
        delete[] spinMatrix[i];
    }
    delete[] spinMatrix;

    ofile.close();
    return 0;
}

/*
    * Initializes the spin Matrix only
*/
void initialize(int dim, int **spinMatrix, double &E, double &M, int initial_state)
{

    double r;
    if (initial_state == 0)
    {
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                spinMatrix[i][j] = 1; // initial orientation all up
            }
        }
    }
    if (initial_state == 1)
    {
        mt19937_64 generator(clock());
        uniform_real_distribution<double> rng(0, 1);
        double r;

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                r = rng(generator);
                spinMatrix[i][j] = r <= 0.5 ? -1 : 1;
            }
        }
    }
}

/*
    * Metropolis algorithm for wether we accept a proposed spin swap or not. 
    * One Montecarlo cycle is said to be a full sweep over the lattice 
    * This means that for a L*L lattice, we will do L^2 number of "shots" at our lattice for each MCs. 
*/
void MonteCarloMetropolis(int dim, int MCs, int **spinMatrix, double T, double *w, double *localValues, int order)
{
    double E = 0.;
    double M = 0.;
    initialize(dim, spinMatrix, E, M, order); // Last arg is initial state: 0 = ordered | 1 = unordered
    equil(spinMatrix, MCs, dim, w);
    getEnergyAndMagneticMoment(dim, spinMatrix, E, M);
    random_device rd;
    mt19937_64 generator(rd());                  // Setups the random number used to seed the RNG
    uniform_real_distribution<double> RNG(0, 1); // Uniform distrubution for x in [0,1]

    int accept = 0;
    int totalSpins = dim * dim;
    for (int cycle = 0; cycle < MCs; cycle++)
    {
        for (int i = 0; i < totalSpins; i++)
        {
            // Choose a random index
            int ri = (int)(RNG(generator) * (double)dim);
            int rj = (int)(RNG(generator) * (double)dim);

            // Find the change in energy
            int nearestNeighbors = (spinMatrix[ri][periodic(rj, dim, -1)] + spinMatrix[ri][periodic(rj, dim, 1)] + spinMatrix[periodic(ri, dim, -1)][rj] + spinMatrix[periodic(ri, dim, 1)][rj]);
            int dE = 2 * spinMatrix[ri][rj] * nearestNeighbors;

            // Random number which decides wether we accept the energy change or not
            double r = RNG(generator);
            if (r <= w[dE + 8] || dE < 0)
            {
                // We accept the proposed spin
                spinMatrix[ri][rj] *= -1;
                M += (double)2 * spinMatrix[ri][rj];
                E += (double)dE;
                accept++;
            }
        }
        // Update the expectation values
        localValues[0] += (double)E;
        localValues[1] += (double)E * (double)E;
        localValues[2] += (double)M;
        localValues[3] += (double)M * M;
        localValues[4] += (double)fabs(M);

        // For number of accepted states and finding equilibrium
        // output2(dim, cycle + 1, T, localValues, accept);

        // Uncomment if you need data for the probability calculations
        // output3(dim, E); // For the probability calculations
    }
    // Write the results from the montecarlo at T to file
    output(dim, MCs, T, localValues);
}

/*
    * Finds the energy and magnetization of the lattice.
    * This is used instead of re initiallizing the matrix each time
*/
void getEnergyAndMagneticMoment(int dim, int **spinMatrix, double &E, double &M)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            M += (double)spinMatrix[i][j];
            E -= (double)spinMatrix[i][j] * (spinMatrix[i][periodic(j, dim, -1)] + spinMatrix[periodic(i, dim, -1)][j]);
        }
    }
}

/*
    * A selfcontained metropolis algorithm, which is only used for the initial equilibration of the lattice
*/
void equil(int **spinMatrix, int MCs, int dim, double *w)
{
    random_device rd;
    mt19937_64 generator(rd());                  // Setups the random number used to seed the RNG
    uniform_real_distribution<double> RNG(0, 1); // Uniform distrubution for x in [0,1]

    int totalSpins = dim * dim;
    for (int cycle = 0; cycle < MCs / 10; cycle++) // We want to discard 10% of the spins. Since MC is greedy, we will still use the full number of cycles for the rest
    {
        for (int i = 0; i < totalSpins; i++)
        {
            int ri = (int)(RNG(generator) * (double)dim);
            int rj = (int)(RNG(generator) * (double)dim);

            int nearestNeighbors = (spinMatrix[ri][periodic(rj, dim, -1)] + spinMatrix[ri][periodic(rj, dim, 1)] + spinMatrix[periodic(ri, dim, -1)][rj] + spinMatrix[periodic(ri, dim, 1)][rj]);
            int dE = 2 * spinMatrix[ri][rj] * nearestNeighbors;

            double r = RNG(generator);
            if (r <= w[dE + 8] || dE < 0)
            {
                spinMatrix[ri][rj] *= -1;
            }
        }
    }
}

/*
    * Output for the expecation values
*/
void output(int dim, int MCs, double T, double *average)
{
    double LL = dim * dim; // Dimension of the matrix
    double TT = T * T;
    double norm = 1.0 / ((double)MCs); // Total number of cycles

    double E = average[0] * norm;
    double EE = average[1] * norm;
    double M = average[2] * norm;
    double MM = average[3] * norm;
    double absM = average[4] * norm;
    double absMM = average[5] * norm;
    double Evariance = (EE - (E * E)) / LL;
    double Mvariance = (MM - (absM * absM)) / LL;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << T;

    ofile << setw(15) << setprecision(8) << E / LL;
    ofile << setw(15) << setprecision(8) << Evariance / TT;

    ofile << setw(15) << setprecision(8) << M / LL;
    ofile << setw(15) << setprecision(8) << Mvariance / T;
    ofile << setw(15) << setprecision(8) << absM / LL;

    ofile << setw(15) << setprecision(8) << EE;
    ofile << setw(15) << setprecision(8) << MM << endl;
}

/*
    * Output for the mean magnetization and mean enegry, including number of accepted states per monte carlo cycle. Cycles are also included
*/
void output2(int dim, int MCs, double T, double *average, int accept)
{
    double LL = dim * dim;             // Dimension of the matrix
    double norm = 1.0 / ((double)MCs); // Total number of cycles

    double E = average[0] * norm;
    double absM = average[4] * norm;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << T;
    ofile << setw(15) << setprecision(8) << MCs;
    ofile << setw(15) << setprecision(8) << accept;
    ofile << setw(15) << setprecision(8) << E / LL;
    ofile << setw(15) << setprecision(8) << absM / LL << endl;
}

/*
    * Output for the a single input. 
*/
void output3(int dim, double E)
{
    double LL = dim * dim; // Dimension of the matrix

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << E << endl;
}
/* 
    * Output for time 
*/
void outputTime(double time)
{
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << time << endl;
}
