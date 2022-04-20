#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#define TAG_PREV 5
#define TAG_SOLVED 6
#define TAG_WRITTED 7

const int TIME = 10;
const int SIZE = 10;
const double TAU = 0.01;
const double H = 0.01;

double f(double x, double t)
{
    return x * t;
}

double phi(double x)
{
    return sin(x);
}

double psi(double t)
{
    return sin(2 * t);
}

int main(int argc, char** argv)
{    
    int size = 0;
    int rank = 0;
    
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
    int finish = 0;
    
    clock_t start_time = 0;
    clock_t stop_time = 0;
    if (rank == 0)
        start_time = clock();
        
    int start_num = rank * SIZE / size;
    int stop_num = (rank + 1) * SIZE / size - 1; // n * rank + n - 1;
    
    int cur_size = stop_num - start_num + 1 + (rank == 0 ? 0 : 1);
        
    double** u_cur = new double* [(int)(TIME / TAU)];
    
    for (int i = 0; i < TIME / TAU; i++)
        u_cur[i] = new double[cur_size];
    
    for (int j = 0; j < cur_size; j++)
        u_cur[0][j] = phi(H * (j + start_num - (rank == 0 ? 0 : 1)));
    
    for (int i = 1; i < TIME / TAU; i++)
    {
        if (rank == 0)
            u_cur[i][0] = psi(i * TAU);
        
        else
            MPI_Recv(&(u_cur[i][0]), 1, MPI_DOUBLE, rank - 1, TAG_PREV, MPI_COMM_WORLD, &status);
        
        for (int j = 1; j < cur_size; j++)
        {
            u_cur[i][j] = (2 * f(H * (j + 1/2), TAU * (i + 1/2)) - 
                (1/TAU - 1/H) * u_cur[i][j - 1] + (1/TAU + 1/H) * u_cur[i - 1][j - 1]
                + (1/TAU - 1/H) * u_cur[i - 1][j])/(1/TAU + 1/H);
        }
        
        if (rank != size - 1)
            MPI_Send(&(u_cur[i][cur_size - 1]), 1, MPI_DOUBLE, rank + 1, TAG_PREV, MPI_COMM_WORLD);
        
    }
    
    if (rank == size - 1)
        MPI_Send(&finish, 1, MPI_INT, 0, TAG_SOLVED, MPI_COMM_WORLD);
    
    if (rank == 0)
    {
        MPI_Recv(&finish, 1, MPI_INT, size - 1, TAG_SOLVED, MPI_COMM_WORLD, &status);
        stop_time = clock();
        printf("Completed in %ld\n", stop_time - start_time);
    }
    
    FILE* fp = nullptr;
    
    if (rank != 0)
        MPI_Recv(&finish, 1, MPI_INT, rank - 1, TAG_WRITTED, MPI_COMM_WORLD, &status);
    
    fp = fopen("solution.txt", rank == 0 ? "w" : "a");
    
    for (int j = (rank == 0 ? 0 : 1); j < cur_size; j++)
    {
      for (int i = 0; i < (int)(TIME / TAU); i++)
        fprintf(fp, "%lg ", u_cur[i][j]);
      
      fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    if (rank != size - 1)
      MPI_Send(&finish, 1, MPI_INT, rank + 1, TAG_WRITTED, MPI_COMM_WORLD);

    MPI_Finalize();
    
    return 0;
}
