#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    if (argc <= 1)
        return 0;
    
    int N = atoi(argv[1]);
    int x = 1;
    
    long int start_time = clock();
    
    long double exp = 1.0;
    long double prev = 1.0;
    long double cur = prev;
    for (int n = 1; n < N + 1; n++)
    {
        cur = prev * x / n;
        exp += cur;
        prev = cur;
    }
    
    long int finish_time = clock();
    
    printf("%Lg, %ld \n", exp, finish_time - start_time);
    
    return 0;
}
