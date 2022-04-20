#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define TAG 5

int main(int argc, char** argv)
{    
    int size = 0;
    int rank = 0;
        
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    long int start_time = 0;
    long int finish_time = 0;
    int N = 0;
    
    
    if (rank == 0)
    {
        start_time = clock();
        MPI_Send(&N, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
        MPI_Recv(&N, 1, MPI_INT, size - 1, TAG, MPI_COMM_WORLD, &status);
        finish_time = clock();
        printf("TIME = %ld\n ", (finish_time - start_time)/size);
    }
    
    else
    {
        
        MPI_Recv(&N, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, &status);
        MPI_Send(&N, 1, MPI_INT, (rank + 1)%size, TAG, MPI_COMM_WORLD);
        
    }
    
    MPI_Finalize();    
    
    return 0;
}

