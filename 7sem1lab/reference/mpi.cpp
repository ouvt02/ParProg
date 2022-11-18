#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <ctime>

long int clk()
{
  timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  long int time_ms = time.tv_sec * 1000 + time.tv_nsec / 1000000;
  return time_ms;
}

#define ISIZE 5000
#define JSIZE 5000

#define FORWARDING 1

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank = 0, comm_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int start = rank * ISIZE / comm_size;
    int stop = (rank + 1) * ISIZE / comm_size - 1;

    //printf("%d, %d\n", start, stop);

    double** a = new double*[rank == 0 ? ISIZE : stop - start + 1];

    FILE *ff;
    long start_time;
    //подготовительная часть – заполнение некими данными
    for (int i = 0; i < stop - start + 1; i++)
    {
        a[i] = new double[JSIZE];
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * (i + start) + j;
        }
    }

    if (rank == 0)
    {
        for (int i = stop - start + 1; i < ISIZE; i++)
            a[i] = new double[JSIZE];
    }

    // требуется обеспечить измерение времени работы данного цикла
    if (rank == 0)
        start_time = clk();

    for (int i = 0; i < stop - start + 1; i++)
    {
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = sin(2 * a[i][j]);
        }
    }
    
    if (rank != 0)
    {
        for (int line = 0; line < stop - start + 1; line++)
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

    if (rank == 0)
    {
        ff = fopen("result_mpi.txt","w");
        
        for(int i = 0; i < ISIZE; i++)
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

    return 0;
}