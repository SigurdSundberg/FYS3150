/*
We will study the ising model, setting boltzman constant to 1 and J = 1.

To narrow down area to work with. We change temperature and then burn in before we 
start sampeling new range.
*/

#include <mpi.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>

#include "lib.h"

using namespace std;

ofstream ofile;

inline int periodic(int i, int dim, int pos)
{
    return (i + dim + pos) % (dim);
}

void initialize(int, int **, int);
void getEnergyAndMagneticMoment(int, int **, double &, double &);
void MonteCarloMetropolis(int, int, int **, double, double, double, double *, double *);
void output(int, int, double, double *);
void outputTime(double);
void Equilibrate(int, int, int **, double *);

int main(int argc, char *argv[])
{
    string filename;
    int dim, MCs, initialArrangementOfLattice;
    double tInitial, tFinal, tStep; // Initial values used

    // MPI initialaztion
    int numberOfProcessors, currentProcessor;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessor);

    // Check number of input argumetns
    if ((currentProcessor == 0) && argc <= 7)
    {
        cout << "Bad Usage: " << argv[0] << "See README.md for how to run the program." << endl;
        exit(1);
    }

    // Read from commandline
    if ((currentProcessor == 0) && argc > 1)
    {
        filename = argv[1];
        cout << filename << endl;
        dim = atoi(argv[2]);
        MCs = atoi(argv[3]);
        initialArrangementOfLattice = atoi(argv[4]);
        tInitial = atof(argv[5]);
        tFinal = atof(argv[6]);
        tStep = atof(argv[7]);
    }

    // Setup output file
    if (currentProcessor == 0)
    {
        string outputFile = filename;
        outputFile += to_string(dim);
        // outputFile += "_";
        // outputFile += to_string(MCs);
        cout << outputFile << endl;
        ofile.open(outputFile, ios_base::app);
        ofile << MCs * numberOfProcessors << endl;
    }

    // Let all the nodes know the common variables
    MPI_Bcast(&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&MCs, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&initialArrangementOfLattice, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tInitial, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tFinal, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tStep, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Allocate memory to spinMatrix
    int **spinMatrix;
    spinMatrix = new int *[dim];
    for (int i = 0; i < dim; i++)
    {
        spinMatrix[i] = new int[dim];
    }

    // Start of the MonteCarlo Sampling, looping over temperatures
    double timeStart, timeFinal, timeTotal;
    timeStart = MPI_Wtime();
    for (double T = tInitial; T <= tFinal; T += tStep)
    {
        double E = 0., M = 0.;
        double w[17];
        for (int dE = -8; dE <= 8; dE++)
        {
            w[dE + 8] = 0;
        }
        for (int dE = -8; dE <= 8; dE += 4)
        { // The energy for the current temperature
            w[dE + 8] = exp(-dE / ((double)T));
        }

        // Define the local expecation values
        double localValues[6];
        for (int i = 0; i < 6; i++)
        {
            localValues[i] = 0.;
        }

        // Setup the spinMatrix once
        if (T == tInitial)
        {
            initialize(dim, spinMatrix, initialArrangementOfLattice);
            Equilibrate(dim, MCs, spinMatrix, w);
        }
        // Find E and M for the current configuration of the spinmatrix.
        // DO NOT KNOW IF THIS IS TOTALLY NEEDED, OR IF I CAN REUSE
        getEnergyAndMagneticMoment(dim, spinMatrix, E, M);

        // Perform the Metropolis algorithm.
        MonteCarloMetropolis(dim, MCs, spinMatrix, T, E, M, w, localValues);

        // Setup the total values for writing to file
        double totalValues[6];
        for (int i = 0; i < 6; i++)
        {
            totalValues[i] = 0.;
        }
        for (int i = 0; i < 6; i++)
        {
            MPI_Reduce(&localValues[i], &totalValues[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }

        // Write the results to file
        if (currentProcessor == 0)
        {
            output(dim, MCs * numberOfProcessors, T, totalValues);
        }
    }
    timeFinal = MPI_Wtime();
    timeTotal = timeFinal - timeStart;
    if (currentProcessor == 0)
    {
        cout << "Time: --- " << timeTotal << " seconds --- on " << numberOfProcessors << " processors." << endl;
        // outputTime(timeTotal);
    }
    if (currentProcessor == 0)
    {
        ofile.close();
    }

    // Free memory
    for (int i = 0; i < dim; i++)
    {
        delete[] spinMatrix[i];
    }
    delete[] spinMatrix;

    MPI_Finalize();
    return 0;
}

void initialize(int dim, int **spinMatrix, int initial_state)
{ // This should be working

    double r;
    /*
    Setup the initial state where we have all spins in the same direction
    */
    if (initial_state == 0)
    {
        // Setup spin matrix and initial magnetization
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                spinMatrix[i][j] = 1; // initial orientation all up
            }
        }
    }
    /*
    Setup the initial state where we have unordered spins
    */
    if (initial_state == 1)
    {
        mt19937_64 generator(clock());
        uniform_real_distribution<double> rng(0, 1);
        double r;

        // Setup spin matrix and initial magnetization
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
    * Metropolis algorithm for wether we accept a proposed spin swap or not. 
    * One Montecarlo cycle is said to be a full sweep over the lattice 
    * This means that for a L*L lattice, we will do L^2 number of "shots" at our lattice for each MCs. 
*/
void MonteCarloMetropolis(int dim, int MCs, int **spinMatrix, double T, double E, double M, double *w, double *localValues)
{
    random_device rd;
    mt19937_64 generator(rd());                  // Setups the random number used to seed the RNG
    uniform_real_distribution<double> RNG(0, 1); // Uniform distrubution for x in [0,1]

    // int accept = 0;
    int totalSpins = dim * dim;
    for (int cycle = 0; cycle < MCs; cycle++)
    {
        // Shooting the lattice
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
            if (r <= w[dE + 8])
            {
                // We accept the proposed spin
                spinMatrix[ri][rj] *= -1;
                M += (double)2 * spinMatrix[ri][rj];
                E += (double)dE;
                // accept++;
            }
        }
        // Update the expectation values
        localValues[0] += (double)E;
        localValues[1] += (double)E * (double)E;
        localValues[2] += (double)M;
        localValues[3] += (double)M * M;
        localValues[4] += (double)fabs(M);
    }
}

void Equilibrate(int dim, int MCs, int **spinMatrix, double *w)
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
            if (r <= w[dE + 8])
            {
                spinMatrix[ri][rj] *= -1;
            }
        }
    }
}

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
    double Evariance = (EE - (E * E)) / LL;
    double Mvariance = (MM - (absM * absM)) / LL;
    // cout << E << " " << EE << " " << M << " " << MM << " " << Evariance << " " << Mvariance << endl;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << T;

    ofile << setw(15) << setprecision(8) << E / LL;
    ofile << setw(15) << setprecision(8) << Evariance / TT;

    ofile << setw(15) << setprecision(8) << M / LL;
    ofile << setw(15) << setprecision(8) << Mvariance / T;
    ofile << setw(15) << setprecision(8) << absM / LL << endl;
}
void outputTime(double time)
{
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << time << endl;
}