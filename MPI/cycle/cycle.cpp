#include <stdio.h>
#include <mpi.h>

#define TAG 5

int main(int argc, char** argv)
{
    if (argc == 1)
    return 0;
    
    int N = atoi(argv[1]);
    
    int size = 0;
    int rank = 0;
    
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int received = 0;
    
    if (rank == 0)
    {
        N++;
        MPI_Send(&N, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
        MPI_Recv(&received, 1, MPI_INT, size - 1, TAG, MPI_COMM_WORLD, &status);
        printf("%d\n ", received);
    }
    
    else
    {
        
        MPI_Recv(&received, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, &status);
        received++;
        MPI_Send(&received, 1, MPI_INT, (rank + 1)%size, TAG, MPI_COMM_WORLD);
        
    }
    
    
    MPI_Finalize();
    
    return 0;
}
