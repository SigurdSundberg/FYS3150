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

void initialize(int, int **, double &, double &, int);
void MonteCarloMetropolis(int, int, double, double *);
void read_input(int &, int &, double &, double &, double &);
void output(int, int, double, double *);
void analytical_2x2_lattice(double *, double);

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
    if ((currentProcessor == 0) && argc <= 6)
    {
        cout << "Bad Usage: " << argv[0] << " outputFile dim MCs initConfig initialTemp finalTemp stepTemp" << endl;
        exit(1);
    }

    // Read from commandline
    if ((currentProcessor == 0) && argc <= 6)
    {
        filename = argv[0];
        dim = atoi(argv[1]);
        MCs = atoi(argv[2]);
        initialArrangementOfLattice = atoi(argv[3]);
        tInitial = atof(argv[4]);
        tFinal = atof(argv[5]);
        tStep = atof(argv[6]);
    }

    // Setup output file
    if (currentProcessor == 0)
    {
        string outputFile = filename;
        outputFile += to_string(dim);
        ofile.open(outputFile);
        ofile << MCs << endl;
    }

    // Let all the nodes know the common variables
    MPI_Bcast(&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&MCs, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&initialArrangementOfLattice, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tInitial, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tFinal, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&tStep, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    /*
    double w[17];

    int **spinMatrix;
    spinMatrix = new int *[dim];
    for (int i = 0; i < dim; i++)
    {
        spinMatrix[i] = new int[dim];
    }
    */

    // Start of the MonteCarlo Sampling, looping over temperatures
    double timeStart, timeFinal, timeTotal;
    timeStart = MPI_Wtime();
    for (double T = tInitial; T <= tFinal; T += tStep)
    {
        /*
        for (int dE = -8; dE <= 8; dE++)
        {
            w[dE + 8] = 0;
        }
        for (int dE = -8; dE <= 8; dE += 4)
        { // The energy for the current temperature
            w[dE + 8] = exp(-dE / ((double)T));
        }
        */
        double expectation[6];
        for (int i = 0; i < 6; i++)
        {
            expectation[i] = 0.;
        }

        // Perform the Metropolis algorithm.
        MonteCarloMetropolis(dim, MCs, T, expectation);
    }

    // Free memory
    for (int i = 0; i < dim; i++)
    {
        delete[] spinMatrix[i];
    }
    delete[] spinMatrix;

    if (currentProcessor == 0)
    {
        ofile.close();
    }

    MPI_Finalize();
    return 0;
}

void initialize(int dim, int **spinMatrix, double &E, double &M, int initial_state)
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
                M += (double)spinMatrix[i][j];
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
                M += (double)spinMatrix[i][j];
            }
        }
    }
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            E -= (double)spinMatrix[i][j] * (spinMatrix[i][periodic(j, dim, -1)] + spinMatrix[periodic(i, dim, -1)][j]);
        }
    }
}
/*
    * Metropolis algorithm for wether we accept a proposed spin swap or not. 
    * One Montecarlo cycle is said to be a full sweep over the lattice 
    * This means that for a L*L lattice, we will do L^2 number of "shots" at our lattice for each MCs. 
*/
void MonteCarloMetropolis(int dim, int MCs, int **spinMatrix, double T, double *w, double *localValues)
{

    double E = 0.;
    double M = 0.;
    initialize(dim, spinMatrix, E, M, 0); // Last arg is initial state: 0 = ordered | 1 = unordered

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
        // cout << localValues[4] << endl;
        // Update the expectation values
        localValues[0] += (double)E;
        localValues[1] += (double)E * (double)E;
        localValues[2] += (double)M;
        localValues[3] += (double)M * M;
        localValues[4] += (double)fabs(M);
    }
    // Write the results from the montecarlo at T to file
    output(dim, MCs, T, localValues);
}

void read_input(int &n_spins, int &mcs, double &initial_temp,
                double &final_temp, double &temp_step)
{
    /*
    Read the input data from terminal, by promts 
    I am looking to do this by using command line agruments. But can set this up untill then
    */
    cout << "Number of Monte Carlo trials =";
    cin >> mcs;
    cout << "Lattice size or number of spins (x and y equal) =";
    cin >> n_spins;
    cout << "Initial temperature with dimension energy=";
    cin >> initial_temp;
    cout << "Final temperature with dimension energy=";
    cin >> final_temp;
    cout << "Temperature step with dimension energy=";
    cin >> temp_step;
} // end of function read_input

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
