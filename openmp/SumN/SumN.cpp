#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    if (argc == 1)
        return 0;
    
    int N = atoi(argv[1]);
    double sum = 0.0;

    #pragma omp parallel for
        for (int i = 1; i < N + 1; i++)
            sum += 1.0/i;

    printf("%f\n", sum);
    
    return 0;
}