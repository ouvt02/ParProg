all: cycle

cycle: cycle.cpp
	mpic++ cycle.cpp -o cycle.out
	
PHONY: exec
exec: cycle
	mpiexec -n 4 ./cycle.out 59
	
PHONY: clean
clean:
	rm cycle.out
