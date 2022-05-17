#include <pthread.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DYNAMIC_STEP

pthread_mutex_t MUTEX;
int num_threads = 0;
int num_tasks = 0;
int n_task = 0;

struct ThreadArgs
{
  double (*f)(double) = nullptr;
  double start = 0;
  double stop = 0;
  double accuracy = 0.0001;
};

double linear(double x)
{
  return x;
}

double quad(double x)
{
  return x * x;
}

double my_func(double x)
{
  return cos(1 / x);
}


#ifdef DYNAMIC_STEP

double integral(double (*f)(double), double start_n, double stop_n, double accuracy)
{
  double integr1 = 0.5 * (f(start_n) + f(stop_n)) * (stop_n - start_n);
  double middle = (start_n + stop_n) / 2;
  double integr2 = 0.5 * (f(start_n) + f(middle)) * (middle - start_n) +
                   0.5 * (f(middle) + f(stop_n)) * (stop_n - middle);

  if (std::abs(integr1 - integr2) < accuracy)
    return integr2;

  return integral(f, start_n, middle, accuracy / 2) + integral(f, middle, stop_n, accuracy / 2);
}

#else

double integral(double (*f)(double), double start_n, double stop_n, double step)
{
  double integr = 0.0;
  double x = start_n;
  while (x < stop_n && stop_n - x >= step)
  {
    integr += 0.5 * (f(x + step) + f(x)) * step;
    x += step;
  }

  return integr;
}

#endif

void* thread_func(void* arg)
{
  ThreadArgs* thread_args = (ThreadArgs*)arg;
  double start = thread_args -> start;
  double stop = thread_args -> stop;
  double accuracy = thread_args -> accuracy;
  double (*f)(double) = thread_args -> f;

  double* integr = new double();

  double interval = (stop - start) / (double)num_tasks;

  bool flag = false;
  while (true)
  {
    pthread_mutex_lock(&MUTEX);
      int cur_task = n_task++;
      if (cur_task >= num_tasks)
        flag = true;
    pthread_mutex_unlock(&MUTEX);

    if (flag)
      break;

    double stop_n = interval * (cur_task + 1) + start;

    double start_n = interval * cur_task + start;

    *integr += integral(f, start_n, stop_n, accuracy);
  }

  return integr;
}


double integrate(double (*f)(double), double start, double stop, double accuracy)
{
  double integral = 0;

  void* part_int;
  pthread_t threads[num_threads];

  ThreadArgs thread_args;
  thread_args.f = f;
  thread_args.start = start;
  thread_args.stop = stop;
  thread_args.accuracy = accuracy;
  n_task = 0;
  for (int i = 0; i < num_threads; i++)
      pthread_create(threads + i, NULL, thread_func, &thread_args);

  for (int i = 0; i < num_threads; i++)
  {
      pthread_join(threads[i], &part_int);
      integral += *(double*)part_int;
      delete (double*)part_int;
  }

  return integral;
}


int main(int argc, char** argv)
{
  if (argc < 4)
    return 1;

  num_threads = atoi(argv[1]);
  num_tasks = pow(num_threads, 4);
  double start = atof(argv[2]);
  double stop = atof(argv[3]);
  double accuracy = 0.000001;

  double result = integrate(my_func, start, stop, accuracy);
  printf("%lg\n", result);

  return 0;
}
