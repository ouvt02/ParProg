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
    double** a = new double*[ISIZE];

    FILE *ff;

    for (int i = 0; i < ISIZE; i++)
    {
        a[i] = new double[JSIZE];

        for (int j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }

    long start_time = clk();

    int num_threads = 8;

    #pragma omp parallel num_threads(num_threads)
    {
        double** copy_a = nullptr;
        int start = omp_get_thread_num() * ISIZE / omp_get_num_threads();
        int stop = (omp_get_thread_num() + 1) * ISIZE / omp_get_num_threads() - 1;

        //printf("thread_num = %d, start = %d, stop = %d\n", omp_get_thread_num(), start, stop);

        if (omp_get_thread_num() != omp_get_num_threads() - 1)
        {
            copy_a = new double*[3];

            for (int i = 0; i < 3; i++)
            {
                copy_a[i] = new double[JSIZE];

                for (int j = 0; j < JSIZE; j++)
                {
                    copy_a[i][j] = a[i + stop + 1][j];
                }
            }
        }

        #pragma omp barrier
        
        for (int i = start; i < stop + 1; i++)
        {
            if (i > ISIZE - 4) break;
            for (int j = 4; j < JSIZE; j++)
            {
                a[i][j] = sin(0.04 * ((i + 3 > stop) ? (copy_a[i - stop + 2][j - 4]) : (a[i + 3][j - 4])));
            }
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