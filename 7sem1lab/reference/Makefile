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

compare: run_linear run_omp run_mpi
	diff result.txt result_omp.txt
	diff result.txt result_mpi.txt

clean:
	rm *.out result*.txt