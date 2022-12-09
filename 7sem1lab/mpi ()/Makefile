all: 1g_linear.out 1g_mpi.out

1g_linear.out: 1g_linear.cpp
	g++ -o 1g_linear.out 1g_linear.cpp

1g_mpi.out: 1g_mpi.cpp
	mpic++ -o 1g_mpi.out 1g_mpi.cpp

run_linear: 1g_linear.out
	./1g_linear.out

run_mpi: 1g_mpi.out
	mpiexec -q -n 4 ./1g_mpi.out

q_run_linear: 1g_linear.out 
	./1g_linear.out 0

q_run_mpi: 1g_mpi.out
	mpiexec -q -n 4 ./1g_mpi.out 0

compare: run_linear run_mpi
	diff result.txt result_mpi.txt

q_compare: q_run_linear q_run_mpi

clean:
	rm *.out result*.txt