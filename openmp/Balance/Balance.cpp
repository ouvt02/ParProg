#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include <vector>

int num_threads = 4;

void clear(std::vector<int> results[], int size)
{
    for (int i = 0; i < size; i++)
        results[i].clear();
}

int main(int argc, char* argv[])
{
    std::vector<int> results[num_threads];

    printf("Without balance\n");

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With static balance, chunk = 1\n");

    #pragma omp parallel for schedule(static, 1) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With static balance, chunk = 4\n");

    #pragma omp parallel for schedule(static, 4) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With dynamic balance, chunk = 1\n");

    #pragma omp parallel for schedule(dynamic, 1) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With dynamic balance, chunk = 4\n");

    #pragma omp parallel for schedule(dynamic, 4) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With guided balance, chunk = 1\n");

    #pragma omp parallel for schedule(guided, 1) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }

    clear(results, num_threads);

    printf("With guided balance, chunk = 4\n");

    #pragma omp parallel for schedule(guided, 4) num_threads(num_threads)
    for (int i = 0; i < 65; i++)
    {
        usleep((omp_get_thread_num() + 1) * 20000);
        results[omp_get_thread_num()].push_back(i);
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Thread %d: ", i);
        for (auto iter: results[i])
            printf("%3d, ", iter);
        
        printf("\n");
    }
}