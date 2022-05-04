#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define TAG 5

long int clk()
{
  timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  long int time_ns = time.tv_sec * 1000000000 + time.tv_nsec;
  return time_ns;
}

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
        start_time = clk();
        for (int i = 0; i < 100000; i++)
        {
            MPI_Send(&N, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
            MPI_Recv(&N, 1, MPI_INT, size - 1, TAG, MPI_COMM_WORLD, &status);
        }

        finish_time = clk();
        printf("TIME = %f\n ", (double)(finish_time - start_time)/(100000 * size));
    }
    
    else
    {
        for (int i = 0; i < 100000; i++)
        {
            MPI_Recv(&N, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, &status);
            MPI_Send(&N, 1, MPI_INT, (rank + 1)%size, TAG, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();    
    
    return 0;
}

