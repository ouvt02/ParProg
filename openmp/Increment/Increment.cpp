#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{    
    int x = 0;
    int thread_num = 0;

    #pragma omp parallel
    {
        while (omp_get_thread_num() != thread_num) ;

        #pragma omp critical
        {
            x++;
            printf("%d, thread %d\n", x, omp_get_thread_num());
            thread_num++;
        }

    }
    
    return 0;
}