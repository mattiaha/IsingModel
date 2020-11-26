# IsingModel

Project4.exe is the program used to calculate the ising model. It uses MPI and Armadillo. It was compiled through Visual Studios, so there might be an issue running it as is. Should that be the case one can compile the cpp files in the program folder. To run the program from the command line, write in "mpiexec -n" followed by number of processors you wish to utilize, followed by "Project4.exe".
After that follows the command line arguments for name of output file, lattice size, MC-cycles, initial temperature, end temperature, temperature step. 
The last argument should be put to 0, as the values 1 or 2 makes the program create text files for determining the number of cycles before equilibrium is reached. We Should we wish to test this, we have to change the value of the shorten-variable to 0. If we don't change the shorten-variable, however, we can produce the energy values needed to plot the histograms for the probability of different energies. 1 indicates the system's initial state being the ground state whereas 2 indicates a randomized initial state. 
The number of MC-cycles for this test can't be equal to or higher than 1000000, as we don't run this by paralellization, and so the program would spend an awfully large amount of time. 

An example of the input in the command line to run the program would be:
mpiexec -n 6 Project4.exe test.txt 20 1000000 2.1 2.4 0 0

The final temperature and temperature step can be set to 0 if one only wishes to look at the Ising model at a certain temperature.

The histogram figures prob_24.png and prob_t1.png were created by running the python-script hist_plot.py with T1P.txt and T24P.txt as input files. The numbers in the names indicate the corresponding temperature. 

The figures of the mean magnetization, mean energy, susceptibility and heat were created by running the python-script plot_ising.py with the files 40s_Tl.txt, 60s_T1, 80s_Tl.txt and 100s_Tl.txt as input. These txt-files were created by running Project4.exe at default setting (last command line-argument 0), using 1000000 MC-cycles, and letting the temperature run from T=2.1 to T=2.35 with a temperature step dT = 0.05

The remaining figures were created by using the python script plot_eq.py with the txt-files ising_eq1.txt , ising_eq1ran.txt , ising_eq2.txt and ising_eq2_rand.txt as input. The numbers indicate if the temperature is T=1.0 or T=2.4. "ran" and "rand" indicates the initial state is randomized, and in the other two text files the initial state is the ground state of the system.
