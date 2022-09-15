#include <stdio.h>
#include <omp.h>

int x = 0;
#pragma omp threadprivate(x)

int main(int argc, char* argv[])
{
    int thread_num = 0;
    x = 5;
    printf("Without copyin\n");
    
    #pragma omp parallel num_threads(3)
    {
        printf("%d, thread %d\n", x, omp_get_thread_num());
    }

    printf("With copyin\n");

    #pragma omp parallel copyin(x) num_threads(3)
    {
        printf("%d, thread %d\n", x, omp_get_thread_num());
    }

    printf("Without copyin\n");

    #pragma omp parallel num_threads(3)
    {
        printf("%d, thread %d\n", x, omp_get_thread_num());
    }

} 