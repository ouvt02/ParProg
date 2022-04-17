#include <stdio.h>
#include <stdlib.h>
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

    int n = N / size;
    
    if (rank == 0)
    {
        float sum = 0;
        for (int i = (size - 1) * n + 1; i < (size - 1) * n + 1 + N - 3 * n; i++)
        {
            sum = sum + 1.0/i;
        }

        for (int r = 1; r < size; r++)
        {
            float temp_sum = 0;
            MPI_Recv(&temp_sum, 1, MPI_FLOAT, r, TAG, MPI_COMM_WORLD, &status);
            sum += temp_sum;
        }
                
        printf("%f\n", sum);
        
    }
    
    else
    {
        float sum = 0;
        for (int i = (size - rank - 1) * n + 1; i < (size - rank - 1) * n + 1 + n; i++)
            sum = sum + 1.0/i;
        
        MPI_Send(&sum, 1, MPI_FLOAT, 0, TAG, MPI_COMM_WORLD);

    }
    
    MPI_Finalize();
    
    return 0;
}
