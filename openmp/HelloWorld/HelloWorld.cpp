#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    int size = 0;
    int rank = 0;
    
    #pragma omp parallel
    {
        printf("Hello world! I am thread %d\n", omp_get_thread_num());
    }
    
    return 0;
}