#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <ctime>

const int ISIZE = 5000;
const int JSIZE = 5000;

long int clk()
{
  timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  long int time_ms = time.tv_sec * 1000 + time.tv_nsec / 1000000;
  return time_ms;
}

int main(int argc, char **argv)
{
    //omp_set_nested(true);

    double** a = new double*[ISIZE];

    FILE *ff;
    //подготовительная часть – заполнение некими данными
    for (int i = 0; i < ISIZE; i++)
    {
        a[i] = new double[JSIZE];
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }
    // требуется обеспечить измерение времени работы данного цикла
    long start_time = clk();

    #pragma omp parallel for schedule(dynamic, 1) num_threads(4)
    for (int i = 0; i < ISIZE; i++)
    {
        //#pragma omp parallel for
        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = sin(2 * a[i][j]);
        }
    }

    printf("OpenMP: %ld mcs\n", clk() - start_time);
    
    if (argc < 2)
    {
        ff = fopen("result_omp.txt","w");
        
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
}