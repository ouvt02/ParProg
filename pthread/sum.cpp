#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

pthread_mutex_t MUTEX;
int num_threads;
int N;

void* func(void* arg)
{
    pthread_mutex_lock(&MUTEX);
        int n_thread = (*(int*)arg)++;
    pthread_mutex_unlock(&MUTEX);
    
    double* sum = new double();;
    int n = N / num_threads;
    
    int stop_num = n * n_thread + n;
    if (n_thread == num_threads - 1)
        stop_num = N;
    
    for (int i = n_thread * n + 1; i < stop_num + 1; i++)
        *sum += 1.0/i;
    
    return sum;
}

int main(int argc, char** argv)
{
    if (argc < 3)
        return 1;
    
    num_threads = atoi(argv[1]);
    N = atoi(argv[2]);
    
    
    int n_thread = 0;
    
    pthread_t threads[num_threads];
    void* part_sum;
    double sum = 0;
    
    for (int i = 0; i < num_threads; i++)
        pthread_create(threads + i, NULL, func, &n_thread);
    
    for (int i = 0; i< num_threads; i++)
    {
        pthread_join(threads[i], &part_sum);
        sum += *(double*)part_sum;
        delete (double*)part_sum;
    }
    
    printf("%lg\n", sum);
        
    return 0;
}
