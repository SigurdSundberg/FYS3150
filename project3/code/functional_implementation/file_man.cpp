#include "file_man.hpp"

using namespace std;

ofstream file;
FILE *init, *mass_;

void readFile(string filename_o, string filename_m, double *x, double *y, double *z, double *vx, double *vy, double *vz, double *mass, int objects)
{
    int n = filename_o.length();
    char object[n + 1], masses[n + 1];
    strcpy(object, filename_o.c_str());
    strcpy(masses, filename_m.c_str());

    init = fopen(object, "r");
    mass_ = fopen(masses, "r");
    for (int i = 0; i < objects; i++)
    {
        fscanf(init, "%lf %lf %lf %lf %lf %lf", &x[i], &y[i], &z[i], &vx[i], &vy[i], &vz[i]);
        fscanf(mass_, "%lf", &mass[i]);
    }
    fclose(init);
    fclose(mass_);
}

void writeToFile(string filename, vec3 pos, int n_body)
{
    if (!file.good())
    {
        file.open(filename.c_str(), ofstream::out);
        if (!file.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    file << n_body << " " << pos[0] << " " << pos[1] << " " << pos[2] << "\n";
}
