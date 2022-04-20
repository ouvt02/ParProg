#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

double** solve_eq()
{
    double** u = new double* [(int)(TIME / TAU)];
    for (int i = 0; i < TIME / TAU; i++)
    {
        u[i] = new double[(int)(SIZE / H)];
        u[i][0] = psi(TAU * i);
    }
        
    for (int j = 0; j < SIZE / H; j++)
        u[0][j] = phi(H * j);

    
    for (int i = 1; i < TIME / TAU; i++)
    {
        for(int j = 1; j < SIZE / H; j++)
        {
            u[i][j] = (2 * f(H * (j + 1/2), TAU * (i + 1/2)) - 
                (1/TAU - 1/H) * u[i][j - 1] + (1/TAU + 1/H) * u[i - 1][j - 1]
                + (1/TAU - 1/H) * u[i - 1][j])/(1/TAU + 1/H);
        }
    }
    return u;
}


int main()
{
    clock_t start_time = clock();
    double** u = solve_eq();
    clock_t stop_time = clock();
    
    for (int i = 0; i < TIME / TAU; i++)
    {
        for(int j = 0; j < SIZE / H; j++)
            printf("%lg ", u[i][j]);
        printf("\n");
    }
    
    
    
    printf("Completed in %ld\n", stop_time - start_time);
    return 0;
}
