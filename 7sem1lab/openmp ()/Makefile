all: 1b_linear.out 1b_omp.out

1b_linear.out: 1b_linear.cpp
	g++ -o 1b_linear.out 1b_linear.cpp

1b_omp.out: 1b_omp.cpp
	g++ -o 1b_omp.out 1b_omp.cpp -fopenmp

run_linear: 1b_linear.out
	./1b_linear.out

run_omp: 1b_omp.out
	./1b_omp.out

compare: run_linear run_omp
	diff result.txt result_omp.txt

clean:
	rm *.out result*.txt