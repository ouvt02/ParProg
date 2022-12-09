all: linear.out mpi.out omp.out

linear.out: linear.cpp
	g++ -o linear.out linear.cpp

omp.out: omp.cpp
	g++ -o omp.out omp.cpp -fopenmp

mpi.out: mpi.cpp
	mpic++ -o mpi.out mpi.cpp

run_linear: linear.out
	./linear.out

run_omp: omp.out
	./omp.out

run_mpi: mpi.out
	mpiexec -q -n 4 ./mpi.out

q_run_linear: linear.out 
	./linear.out 0

q_run_mpi: mpi.out
	mpiexec -q -n 4 ./mpi.out 0

q_run_omp: omp.out
	./omp.out 0

compare: run_linear run_omp run_mpi
	diff result.txt result_omp.txt
	diff result.txt result_mpi.txt

q_compare: q_run_linear q_run_mpi q_run_omp

clean:
	rm *.out result*.txt