#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define TAG 5

int main(int argc, char** argv)
{
    if (argc <= 1)
        return 0;
    
    int x = 1;
    
    int N = atoi(argv[1]);
   
    int size = 0;
    int rank = 0;
    
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    long int start_time = clock();

    
    int n = N / size;
    
    long double exp = 1.0;
    long double prev = 1.0;
    long double cur = prev;
    
    int stop_num = n * rank + n;
    if (rank == size - 1)
        stop_num = N;
    
    for (int i = rank * n + 1; i < stop_num; i++)
    {
        cur = prev * x / i;
        exp += cur;
        prev = cur;
    }
    
    long double mult = prev * x / stop_num;
    if (rank != size - 1)
    {
        long double next_part = 0;
        MPI_Recv(&next_part, 1, MPI_LONG_DOUBLE, rank + 1, TAG, MPI_COMM_WORLD, &status);
        next_part = next_part * mult;
        exp = exp + next_part;
    }
    
    if (rank != 0)
        MPI_Send(&exp, 1, MPI_LONG_DOUBLE, rank - 1, TAG, MPI_COMM_WORLD);
    
    
    long int finish_time = clock();
    if (rank == 0)
        printf("%.30Lg, %ld\n", exp, finish_time - start_time);
    
    MPI_Finalize();
    
    return 0;
}
