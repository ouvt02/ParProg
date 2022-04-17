all: hello_world

hello_world: hello_world.cpp
	mpic++ hello_world.cpp -o hello_world.out
	
PHONY: exec
exec: hello_world
	mpiexec -n 4 ./hello_world.out
	
PHONY: clean
clean:
	rm hello_world.out
