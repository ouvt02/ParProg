#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

pthread_mutex_t MUTEX;
int num_threads;

void* func(void* arg)
{
    pthread_mutex_lock(&MUTEX);
        int n_thread = (*(int*)arg)++;
    pthread_mutex_unlock(&MUTEX);
    
    printf("Hello world! thread %d, number of threads %d\n", n_thread, num_threads);
    
    return nullptr;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;
    
    num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];
    int n_thread = 0;
    
    pthread_mutex_init(&MUTEX, NULL);
    
    for (int i = 0; i < num_threads; i++)
        pthread_create(threads + i, NULL, func, &n_thread);
    
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
    
    pthread_mutex_destroy(&MUTEX);
    
    return 0;
}
