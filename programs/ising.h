#pragma once
#ifndef ISING_H
#define ISING_H

#include <armadillo>
#include <cmath>

#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace arma;

class Ising {
public:
	void initialize(int n_spins, mat& SpinMatrix, double& E, double& M, long& idum, double temp, vec w, bool ran);
	void metropolis(int n_spins, long& idum, mat& SpinMatrix, double& E, double& M, vec w);
	void output(int, int, double, vec);
	
};


#endif // ISING_H