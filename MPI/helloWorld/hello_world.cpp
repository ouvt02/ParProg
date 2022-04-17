#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int size = 0;
    int rank = 0;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    printf("Hello world! size = %d, rank = %d\n", size, rank);
    
    MPI_Finalize();
    
    return 0;
}


