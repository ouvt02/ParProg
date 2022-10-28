#pragma once
#include "complex.cpp"
#include "cmath"
#include "algorithm"
#include <omp.h>

void DFT(long int length, const double* signal, Complex* spectre)
{
    for (int k = 0; k < length; k++)
    {
        for (int i = 0; i < length; i++)
            spectre[k] = spectre[k] + Complex(signal[i], 0) * 
                        Complex::e_in_pow(Complex(0, -2 * M_PI * k * i / length));
    }
}

void FFT(long int length, const double* signal, Complex* spectre, bool parallel = true)
{
    #pragma omp parallel for schedule(static, 4) if(parallel)
    for (int i = 0; i < length; i++)
        spectre[i] = Complex(signal[i], 0);

    int j = 1;
    for (int i = 1; i < length * 2; i += 2)
    {
        if (j > i)
            std::swap(spectre[i / 2], spectre[j / 2]);

        int m;
        for (m = length; m >= 2 and j > m; m /= 2) 
            j -= m;

        j += m;
    }

    for (int Mmax = 1; Mmax < length; Mmax *= 2)
    {
        Complex Wp = Complex(sin(-M_PI / (Mmax * 2)) * sin(-M_PI / (Mmax * 2)) * 2, -sin(-2 * M_PI / (Mmax * 2)));
        int num_trs = parallel ? (Mmax < 8 ? Mmax : 8) : 1;
        #pragma omp parallel num_threads(num_trs) if(parallel)
        {
            Complex W = Complex(1, 0);
            int tr_num = omp_get_thread_num();
            int start = Mmax / num_trs * tr_num;
            int stop = tr_num == num_trs - 1 ? Mmax : start + Mmax / num_trs;

            for (int i = 0; i < start; i++)
            {
                W = Complex(W.real - (W.real * Wp.real + W.image * Wp.image),
                        W.image + W.real * Wp.image - W.image * Wp.real);
            }

            for (int m = start; m < stop; m++)
            {
                W = Complex(W.real - (W.real * Wp.real + W.image * Wp.image),
                        W.image + W.real * Wp.image - W.image * Wp.real);

                #pragma omp parallel for schedule(static, 4) if(parallel)
                for (int i = m; i < length; i += Mmax * 2)
                {
                    Complex tmp = W * spectre[i + Mmax];
                    spectre[i + Mmax] = spectre[i] - tmp;
                    spectre[i] = spectre[i] + tmp;
                }
            }
        }

        
    }
    #pragma omp parallel for schedule(static, 4) if(parallel)
    for (int i = 0; i < length / 2; i++)
        std::swap(spectre[i], spectre[length - 1 - i]);
}
