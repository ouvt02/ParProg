all: sum

sum: sum.cpp
	mpic++ sum.cpp -o sum.out
	
PHONY: exec
exec: sum
	mpiexec -n 4 ./sum.out 10000
	
PHONY: clean
clean:
	rm sum.out
