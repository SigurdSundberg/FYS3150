# Project 4: The Ising model
In this folder there are 2 subfolders [code](https://github.com/SigurdSundberg/FYS3150/tree/master/project4/code), [report](https://github.com/SigurdSundberg/FYS3150/tree/master/project4/report).
Which contains what is self explanatory.
## Code
All the code was run on the following specs:

Computer  : Lenovo IdeaPad Flexx 5 14IIL05<br />
Version   : Ubuntu 20.04 1 LTS <br />
Processor : Intel Core i5-1035G1 Processor 6MB @ 1.00GHz x8 <br />
Memory    : 8.0GB DDR4-3200 DDR4 Soldered 3200MHz <br />
Graphics  : Mesa Intel® UHD Graphics (ICL GT1) <br />

To compile the code the makefile is included. With `make` creating the unparallelized version of the program and `make mpi` creates the parallelized version of the program. 
The are run in the following way 
`./main [filename] [dim] [Monte Carlo cycles] [Initial configuration(0/1)] [t_initial] [t_final] [t_step]`.
For the parallelized version it is
`mpirun -np [number of processors] ./paraIsing [filename] [dim] [Monte Carlo cycles] [Initial configuration(0/1)] [t_initial] [t_final] [t_step]`.

Regarding the inclusion of unit tests in the Monte Carlo simulation. The only tests which we have essentially done is comparing our implementation of the algorithm to a fixed lattice for which we know the analytical values. Another test which could have been implemented is checking the co-variance of the MersenneTwister. However this is a well tested RNG which this would not be ideal. If we used a self implemented RNG, this test could be exellent. 
