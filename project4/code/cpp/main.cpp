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
void read_input(int &, int &, double &, double &, double &);
void output(int, int, double, double *);
void output2(int, int, double, double *, int);
void output3(int, int, double *);
void outputTime(double);
void analytical_2x2_lattice(double *, double);

int main(int argc, char const *argv[])
{
    /*
    dim = The number of individual spins (L) in the system. LxL dimensional lattice
    MCs = Number of MonteCarlo cycles
    */
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
    cout << filename << " " << dim << " " << MCs << " " << order << " " << T_initial << " " << T_final << " " << T_step << endl;

    filename += argv[2];
    cout << filename << endl;

    int **spinMatrix;
    spinMatrix = new int *[dim];
    for (int i = 0; i < dim; i++)
    {
        spinMatrix[i] = new int[dim];
    }

    // spinMatrix = (int **)matrix(dim, dim, sizeof(int));
    auto start = chrono::high_resolution_clock::now();

    ofile.open(filename, ios_base::app);
    for (double T = T_initial; T <= T_final; T += T_step)
    {
        // Setup the inital values for E and M
        E = 0.;
        M = 0.;
        // Setup possible energy values
        for (int dE = -8; dE <= 8; dE++)
        {
            w[dE + 8] = 0;
        }
        for (int dE = -8; dE <= 8; dE += 4)
        { // The energy for the current temperature
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
    string tFilename = filename;
    auto finish = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / pow(10, 9);
    outputTime(time);
    // COmment to save
    // Free memory
    for (int i = 0; i < dim; i++)
    {
        delete[] spinMatrix[i];
    }
    delete[] spinMatrix;

    // free_matrix((void **)spinMatrix);
    ofile.close();
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
void MonteCarloMetropolis(int dim, int MCs, int **spinMatrix, double T, double *w, double *localValues, int order)
{
    double E = 0.;
    double M = 0.;
    initialize(dim, spinMatrix, E, M, order); // Last arg is initial state: 0 = ordered | 1 = unordered

    random_device rd;
    mt19937_64 generator(rd());                  // Setups the random number used to seed the RNG
    uniform_real_distribution<double> RNG(0, 1); // Uniform distrubution for x in [0,1]

    int accept = 0;
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
            if (r <= w[dE + 8] || dE < 0)
            {
                // We accept the proposed spin
                spinMatrix[ri][rj] *= -1;
                M += (double)2 * spinMatrix[ri][rj];
                E += (double)dE;
                accept++;
            }
        }
        // cout << localValues[4] << endl;
        // Update the expectation values
        localValues[0] += (double)E;
        localValues[1] += (double)E * (double)E;
        localValues[2] += (double)M;
        localValues[3] += (double)M * M;
        localValues[4] += (double)fabs(M);
        // output2(dim, cycle + 1, T, localValues, accept); // For number of accepted states and finding equilibrium

        // if (/* condition */)
        // {
        //     /* code */
        //     // output3(dim, cycle, localValues)
        // }
    }
    // Write the results from the montecarlo at T to file
    // output(dim, MCs, T, localValues);
}

/* 
    **  read_input() from the sample codes from FYS-3150.
    **  This is used for easy access running, instead of having 
    **  to pass command line args.
*/
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
void output3(int dim, int MCs, double *average)
{
    double LL = dim * dim;             // Dimension of the matrix
    double norm = 1.0 / ((double)MCs); // Total number of cycles

    double E = average[0] * norm;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << E / LL << endl;
}
void outputTime(double time)
{
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << time << endl;
}
/*
    * This part of the project can be handeled in python instead. 
    * It will be an easier implementation for it
    * Delete this at some point
*/
void analytical_2x2_lattice(double *A_values, double T)
{
    // Interesting values
    double Z, E, M, EE, MM, absM, absMM, beta;

    int n_spins = 4; // 2x2 we have 4 spins.

    beta = 1 / T; // k_B = 1

    // Analytical expectation values
    Z = 4 * (3 + cosh(8 * beta));
    E = -32 * sinh(8 * beta) / Z;
    EE = 256 * cosh(8 * beta) / Z;
    M = 0;
    MM = 32 * (exp(8 * beta) + 1) * beta / Z;
    absM = 8 * (exp(8 * beta) + 2) / Z;
    absMM = (32 * exp(8 * beta) + 4) / Z;

    // Stores the analytical values for a spesific T
    A_values[0] = E / n_spins;
    A_values[1] = EE / n_spins;
    A_values[2] = absM / n_spins;
    A_values[3] = absMM / n_spins;
    A_values[4] = M / n_spins;
    A_values[5] = MM / n_spins;
    A_values[6] = (A_values[1] - A_values[0] * A_values[0]) * beta * beta; //Heat Capacity
    A_values[7] = (A_values[5]) * beta;                                    //Magnetic susceptibility
}