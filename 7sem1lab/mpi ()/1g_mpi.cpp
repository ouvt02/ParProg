#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <mpi.h>

#define ISIZE 5000
#define JSIZE 5000

#define FORWARDING 1

long int clk()
{
  timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  long int time_ms = time.tv_sec * 1000 + time.tv_nsec / 1000000;
  return time_ms;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank = 0, comm_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int start = rank * ISIZE / comm_size;
    int stop = (rank + 1) * ISIZE / comm_size - 1;

    double** a = new double*[rank == 0 ? ISIZE : stop - start + 2];
    
    FILE *ff;
    long start_time;

    for (int i = 0; i < stop - start + (rank == 0 ? 1 : 2); i++)
    {
        a[i] = new double[JSIZE];
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * (i + start - (rank == 0 ? 0 : 1)) + j;
        }
    }

    if (rank == 0)
    {
        for (int i = stop - start + 1; i < ISIZE; i++)
            a[i] = new double[JSIZE];

        start_time = clk();
    }

    for (int j = 3; j < JSIZE - 1; j++)
    {
        if (rank != 0 && j < JSIZE - 4)
            MPI_Recv(&(a[0][j]), 1, MPI_DOUBLE, rank - 1, FORWARDING, MPI_COMM_WORLD, &status);

        for (int i = 1; i < stop - start + (rank == 0 ? 1 : 2); i++)
        {
            a[i][j] = sin(2 * a[i - 1][j - 3]);
            if (i == stop - start + (rank == 0 ? 0 : 1) && j < JSIZE - 4 && rank != comm_size - 1)
                MPI_Send(&(a[i][j]), 1, MPI_DOUBLE, rank + 1, FORWARDING, MPI_COMM_WORLD);
        }
    }

    if (rank != 0)
    {
        for (int line = 1; line < stop - start + 2; line++)
            MPI_Send(a[line], JSIZE, MPI_DOUBLE, 0, FORWARDING, MPI_COMM_WORLD);
    }


    else 
    {
        for (int i = 1; i < comm_size; i++)
        {
            int own_start = i * ISIZE / comm_size;
            int own_stop = (i + 1) * ISIZE / comm_size - 1;

            for (int line = own_start; line < own_stop + 1; line++)
                MPI_Recv(a[line], JSIZE, MPI_DOUBLE, i, FORWARDING, MPI_COMM_WORLD, &status);
        }
    }

    if (rank == 0)
        printf("MPI: %ld mcs\n", clk() - start_time);

    if (rank == 0 && argc < 2)
    {
        ff = fopen("result_mpi.txt","w");
    
        for (int i = 0; i < ISIZE; i++)
        {
            for (int j = 0; j < JSIZE; j++)
            {
                fprintf(ff,"%f ",a[i][j]);
            }

            fprintf(ff,"\n");
        }

        fclose(ff);
    }

    MPI_Finalize();
}