#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "ft.cpp"
#include <ctime>

long clk()
{
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    long int time_ms = time.tv_sec * 1000000 + time.tv_nsec / 1000;
    return time_ms;
}

double* read_signal(long count)
{
    double* signal = new double[count];
    char filename[100] = {};
    sprintf(filename, "signals/%ld/signal.txt", count);

    FILE* signal_file = fopen(filename, "r");
    int n = 0;
    while (fscanf(signal_file, "%lf", &(signal[n++])) == 1) ;
    fclose(signal_file);

    printf("Readed signal from %s\n", filename);

    return signal;
}

void write_spectre_abs(Complex* spectre, long count)
{
    char filename[100] = {};
    sprintf(filename, "signals/%ld/spectre.txt", count);

    FILE* spectre_file = fopen(filename, "w");
    for (int i = 0; i < count; i++)
        fprintf(spectre_file, "%.4lf ", spectre[i].abs());
    fclose(spectre_file);

    printf("Writed spectre from %s\n", filename);
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("Comparing DFT with FFT\n\n");

        double signal[8] = {0.1, 0.5, 1.1, 1.1, 0.9, 0.3, -0.1, -0.5};

        Complex* spectre = new Complex[8];

        DFT(8, signal, spectre);
        for (int i = 0; i < 8; i++)
            printf("%lf + %lfi\n", spectre[i].real, spectre[i].image);
            
        printf("\n");
        
        FFT(8, signal, spectre);
        for (int i = 0; i < 8; i++)
            printf("%lf + %lfi\n", spectre[i].real, spectre[i].image);
    }
    
    else
    {
        long points = atol(argv[1]);
        printf("Calculatig spectre for %ld points\n", points);

        double* signal = read_signal(points);
        Complex* spectre = new Complex[points];

        long start_time = clk();
        FFT(points, signal, spectre, false);
        printf("Linear   FFT calculated in %ld mks for %ld points\n", clk() - start_time, points);

        start_time = clk();
        FFT(points, signal, spectre, true);
        printf("Parallel FFT calculated in %ld mks for %ld points\n", clk() - start_time, points);

        write_spectre_abs(spectre, points);
    }

    return 0;
}