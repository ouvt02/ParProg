all: 1b_linear.out 1b_omp.out

1b_linear.out: 1b_linear.cpp
	g++ -o 1b_linear.out 1b_linear.cpp

1b_omp.out: 1b_omp.cpp
	g++ -o 1b_omp.out 1b_omp.cpp -fopenmp

run_linear: 1b_linear.out
	./1b_linear.out

run_omp: 1b_omp.out
	./1b_omp.out

q_run_linear: 1b_linear.out 
	./1b_linear.out 0

q_run_omp: 1b_omp.out
	./1b_omp.out 0

compare: run_linear run_omp
	diff result.txt result_omp.txt

q_compare: q_run_linear q_run_omp

clean:
	rm *.out result*.txt