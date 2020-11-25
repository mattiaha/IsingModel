#include "mpi.h"
#include "Random_class.h"
#include "Ising.h"

ofstream ofile;
Ising Is;
int main(int argc, char* argv[]) {
	char* outfilename;
	long idum;
	double initial_temp, final_temp, E, M, temp_step;
	int n_spins, mcs, my_rank, numprocs, find_equilibreum; 
	int shorten = 500;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	if (my_rank == 0 && argc <= 7) {
		cout << "Bad Usage: " << argv[0] <<
			" read output file, Number of spins, MC cycles, initial and final temperature and tempurate step, and select if you want to find MC cycles for equilibreum" << endl;
		exit(1);
	}
	if (my_rank == 0 && argc > 1) {
		outfilename = argv[1];
		ofile.open(outfilename);
		n_spins = atoi(argv[2]);
		mcs = atoi(argv[3])-shorten;
		initial_temp = atof(argv[4]);
		final_temp = atof(argv[5]);
		temp_step = atof(argv[6]);
		find_equilibreum = atoi(argv[7]);

	}

	

	MPI_Bcast(&n_spins, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&mcs, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&initial_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&find_equilibreum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	idum = -1 - my_rank;
	


	int no_intervalls = mcs / numprocs;
	int myloop_begin = my_rank * no_intervalls + 1;
	int myloop_end = (my_rank + 1) * no_intervalls;
	if ((my_rank == numprocs - 1) && (myloop_end < mcs)) myloop_end = mcs;

	mat SpinMatrix = zeros<mat>(n_spins, n_spins);
	vec w(17), average(5), total_average(5);
	if (find_equilibreum == 1) {
		if (mcs >= (1000000)) {
			cout << "too many mc-cycles" << endl;
			exit(2);
		}
		bool ran = false;
		Is.initialize(n_spins, SpinMatrix, E, M, idum, initial_temp, w, ran);
		for (int i = 0; i < 5; i++) average(i) = 0.;
		for (int i = 0; i < 5; i++) total_average(i) = 0.;
		for (int i = 0; i < mcs; i++) {

			Is.metropolis(n_spins, idum, SpinMatrix, E, M, w);
			ofile << setiosflags(ios::showpoint | ios::uppercase);
			ofile << setw(15) << setprecision(8) << E ;
			ofile << setw(15) << setprecision(8) << abs(M) << endl;
		}
		
	}
	else if (find_equilibreum == 2) {
		if (mcs >= (1000000)) {
			cout << "too many mc-cycles" << endl;
			exit(2);
		}
		bool ran = true;
		Is.initialize(n_spins, SpinMatrix, E, M, idum, initial_temp, w, ran);
		for (int i = 0; i < 5; i++) average(i) = 0.;
		for (int i = 0; i < 5; i++) total_average(i) = 0.;
		// initialise array for expectation values



		for (int i = 0; i < mcs; i++) {

			Is.metropolis(n_spins, idum, SpinMatrix, E, M, w);

			ofile << setiosflags(ios::showpoint | ios::uppercase);
			ofile << setw(15) << setprecision(8) << E;
			ofile << setw(15) << setprecision(8) << abs(M) << endl;
		}

	}
	else {
		
		double  TimeStart, TimeEnd, TotalTime;
		TimeStart = MPI_Wtime();
		if (final_temp == 0 && temp_step == 0) {
			bool ran = true;
			
			Is.initialize(n_spins, SpinMatrix, E, M, idum, initial_temp, w, ran);
			for (int i = 0; i < 5; i++) average(i) = 0.;
			for (int i = 0; i < 5; i++) total_average(i) = 0.;
			
			for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {

				Is.metropolis(n_spins, idum, SpinMatrix, E, M, w);

				average(0) += E; average(1) += E * E;average(2) += M; average(3) += M * M; average(4) += fabs(M);
			}

			// Find total average
			for (int i = 0; i < 5; i++) {
				MPI_Reduce(&average[i], &total_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
			}
			// print results
			if (my_rank == 0) {
				Is.output(n_spins, mcs, initial_temp, total_average);
			}

		}
		else {
			for (double temperature = initial_temp; temperature <= final_temp; temperature += temp_step) {
				bool ran = true;
				Is.initialize(n_spins, SpinMatrix, E, M, idum, initial_temp, w, ran);
				
				for (int i = 0; i < 5; i++) average(i) = 0.;
				for (int i = 0; i < 5; i++) total_average(i) = 0.;
				for (int i=0;i< shorten ;i++){
					Is.metropolis(n_spins, idum, SpinMatrix, E, M, w);

				}
				for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {
					Is.metropolis(n_spins, idum, SpinMatrix, E, M, w);

					average(0) += E;average(1) += E * E;average(2) += M;average(3) += M * M;average(4) += fabs(M);


				}

				// Find total average
				for (int i = 0; i < 5; i++) {
					MPI_Reduce(&average[i], &total_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
				}
				// print results
				if (my_rank == 0) {
					Is.output(n_spins, mcs, temperature, total_average);
				}

			}
		}
		ofile.close();
		TimeEnd = MPI_Wtime();
		TotalTime = TimeEnd - TimeStart;
		if (my_rank == 0) {
			cout << "Time = " << TotalTime << " on number of processors: " << numprocs << endl;
		}
	}
	
	// End MPI
	MPI_Finalize();
	return 0;
}


