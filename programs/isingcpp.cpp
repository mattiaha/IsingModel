#include "ising.h"
#include "Random_class.h"
ofstream ofile;
inline int periodic(int i, int limit, int add) {
	return (i + limit + add) % (limit);
}


void Ising::metropolis(int n_spins, long& idum, mat& SpinMatrix, double& E, double& M, vec w) {
	Random rnd;

	for (int y = 0; y < n_spins; y++) {
		for (int x = 0; x < n_spins; x++) {
			//select random spins
			int ix = rnd.ran2(&idum) * (double)n_spins;
			int iy = rnd.ran2(&idum) * (double)n_spins;
			// calculate change in energy
			int deltaE = 2 * SpinMatrix(iy, ix) *
				(SpinMatrix(iy, periodic(ix, n_spins, -1)) +
					SpinMatrix(periodic(iy, n_spins, -1), ix) +
					SpinMatrix(iy, periodic(ix, n_spins, 1)) +
					SpinMatrix(periodic(iy, n_spins, 1), ix));

			//test probability
			if (rnd.ran2(&idum) <= w(deltaE + 8)) {
				SpinMatrix(iy, ix) *= -1;  // flip one spin and accept new spin config
				M += (double)2 * SpinMatrix(iy, ix);
				E += (double)deltaE;

			}
		}
	}
}

void Ising::output(int n_spins, int mcs, double temperature, vec total_average) {
	double norm = 1 / ((double)(mcs));  // divided by total number of cycles 

	double Etotal_average = total_average[0] * norm;
	double E2total_average = total_average[1] * norm;



	double Mtotal_average = total_average[2] * norm;
	double M2total_average = total_average[3] * norm;
	double Mabstotal_average = total_average[4] * norm;
	// all expectation values are per spin, divide by 1/n_spins/n_spins
	double Evariance = (E2total_average - Etotal_average * Etotal_average) / ((double)(n_spins) * (double)(n_spins));
	double Mvariance = (M2total_average - Mtotal_average * Mtotal_average) / ((double)(n_spins) * (double)(n_spins));
	ofile << setiosflags(ios::showpoint | ios::uppercase);
	ofile << setw(15) << setprecision(8) << temperature;
	ofile << setw(15) << setprecision(8) << Etotal_average / ((double)(n_spins) * (double)(n_spins));
	ofile << setw(15) << setprecision(8) << Evariance / (double)(temperature * temperature);
	ofile << setw(15) << setprecision(8) << Mtotal_average / ((double)(n_spins) * (double)(n_spins));
	ofile << setw(15) << setprecision(8) << Mvariance / (double)temperature;
	ofile << setw(15) << setprecision(8) << Mabstotal_average / ((double)(n_spins) * (double)(n_spins)) << endl;
}

void Ising::initialize(int n_spins, mat& SpinMatrix, double& E, double& M, long& idum, double temp, vec w, bool ran) {
	Random rnd;
	E = 0.;
	M = 0.;
	// setup spin matrix and intial magnetization
	if (ran == true) {
		for (int y = 0; y < n_spins; y++) {
			for (int x = 0; x < n_spins; x++) {
				if (rnd.ran2(&idum) <= 0.5) {
					SpinMatrix(y, x) = 1; // spin orientation for the random
				}
				else {
					SpinMatrix(y, x) = -1;

				}
				M += double(SpinMatrix(y, x));
			}
		}
	}
	else {
		for (int y = 0; y < n_spins; y++) {
			for (int x = 0; x < n_spins; x++) {
				SpinMatrix(y, x) = 1; // spin orientation for the ground state
				M += (double)SpinMatrix(y, x);

			}
		}
	}

	// setup initial energy
	for (int y = 0; y < n_spins; y++) {
		for (int x = 0; x < n_spins; x++) {
			E -= (double)SpinMatrix(y, x) *
				(SpinMatrix(periodic(y, n_spins, -1), x) +
					SpinMatrix(y, periodic(x, n_spins, -1)));
		}
	}
	for (int de = -8; de <= 8; de++) w(de + 8) = 0;
	for (int de = -8; de <= 8; de += 4) w(de + 8) = exp(-de / temp);
	
}


