#include <stdio.h>
#include <omp.h>

void print_info()
{
    int lvl = omp_get_level();
    printf("%sПоток %d из %d, предок %d из %d\n", lvl == 1 ? "" : lvl == 2 ? "\t" : "\t\t",
            omp_get_thread_num(), omp_get_num_threads(), 
            omp_get_ancestor_thread_num(lvl - 1), omp_get_team_size(lvl - 1));
}

int main(int argc, char* argv[])
{
    omp_set_nested(true);
    #pragma omp parallel num_threads(4)
    {
        print_info();

        #pragma omp parallel num_threads(3)
        {
            print_info();
        
            #pragma omp parallel num_threads(2)
            {
                print_info();

            }
        }   
    }
}