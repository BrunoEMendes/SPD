#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <omp.h>

#include "main.h"
#include "sort.h"
#include "sequential_no_optimization.h"
#include "sequential_with_optimization.h"
#include "pthreads_2.h"
#include "pthreads_3.h"
#include "pthread_arg_struct.h"
#include "pthreads_n_threads.h"
#include "unittests.h"


#define foreach( ptrvar, strvar, n) char ** ptrvar; for( ptrvar = strvar ;ptrvar < (ptrvar + n); *ptrvar++)

// variáveis globais que definem se vai existir print de output, tempo, e define qual funçao de sort se utiliza



void print_string_array(char ** input_string, int n)
{
    foreach(p1, input_string, n)
        printf("%s\n", *p1);
}

// prints the factors
void print_factors(long * input_string, int n, char * factor)
{
    printf("Factors\n");
    for(int i = 0; i < n; i++)
        printf("%ld\n", input_string[i]);
}

int main(int argc, char ** argv)
{
    int c;
    static char optstring[] = "khqimputs:d:l:";

    int n = 0;
    double total_time, start_time, get_function_run_time();
    //from https://tutoria.ualg.pt/2019/pluginfile.php/132031/mod_resource/content/1/00-Revis%C3%B5es.html
    while ( (c = getopt(argc, argv, optstring)) != -1 )
      switch (c) {
         case 'h':
            printf("Command list:\n\
h -> for help\n\
q -> qsort\n\
i -> to use insertion sort\n\
m -> to use merge sort\n\
p -> enables output prints\n\
u -> runs unit tests\n\
t -> enables time tests\n\
s: -> sequential function\n\
d: -> pthread function\n\
l: -> runs functions in loop\n");
            break;
        case 'q':
            printf("Sorting the function with qSort sort\n");
            q_sort = 1;
            break;
        case 'i':
            printf("Sorting the function with insertion sort\n");
            i_sort = 1;
            if(merge_sort == 1)
                printf("Insertion sort And MergeSort option Selected, Running MergeSort only\n");
            break;
        case 'm':
            printf("Sorting the function with merge sort\n");
            merge_sort = 1;
            if(i_sort == 1)
                printf("Insertion sort And Merge Sort option Selected, Running MergeSort only\n");
            break;
        case 'p':
            printf("Found option p and prints are active\n");
            print_output = 1;
            break;
         case 'u':
            printf("Found option u and it will run unit tests\n");
            unit_tests();
            break;
        case 't':
            printf("Found option t and it count execution time of the program\n");
            time_output = 1;
            break;
        case 'k':
            printf("Running openMP\n");
            test_openMP(argv[optind]);
            break;
        case 's':
            printf("Running Sequential with arg %s\n", optarg);
            if(strcmp(optarg, "1") == 0)
                sequential_default(argv[optind++]);
            else if(strcmp(optarg, "2") == 0)
                sequential_optimization(argv[optind++]);
            else
                printf("Not input_string valid argument, try with:\n\
1 -> for default sequential\n\
2 -> for sequential with otimization\n");
            break;
        case 'd':
            printf("Running Pthreads with arg %s\n", optarg);
            if(strcmp(optarg, "1") == 0)
                pthread_default(argv[optind++]);
            else if(strcmp(optarg, "2") == 0)
                pthread_default_with_3_threads(argv[optind++]);
            else if(strcmp(optarg, "3") == 0)
                pthread_optimzation_with_custom_number_of_threads(argv[optind++]);
            else if(strcmp(optarg, "4") == 0)
                pthread_with_mutex(argv[optind++]);
            else
                printf("Not input_string valid argument\n\
1 -> for pthread function with 2 pthreads\n\
2 -> for pthread function with 3 pthreads\n\
3 -> for pthread function with N threads\n\
4 -> for pthread function with N threads with mutexes\n");
            break;
        case 'l':
            // printf("Running functions in loop 100 times with arg %s\n", optarg);
            for(int i = 0; i < 100; i++)
            {
                start_time=get_function_run_time();
                if(strcmp(optarg, "1") == 0)
                    sequential_default(argv[optind]);
                else if(strcmp(optarg, "2") == 0)
                    sequential_optimization(argv[optind]);
                else if(strcmp(optarg, "3") == 0)
                    pthread_default(argv[optind]);
                else if(strcmp(optarg, "4") == 0)
                    pthread_default_with_3_threads(argv[optind]);
                else if(strcmp(optarg, "5") == 0)
                    pthread_optimzation_with_custom_number_of_threads(argv[optind]);
                else if(strcmp(optarg, "6") == 0)
                    pthread_with_mutex(argv[optind]);
                else if(strcmp(optarg, "7") == 0)
                    test_openMP(argv[optind]);
                // total_time += get_function_run_time() - start_time;
            }
            // printf("total run time %lf\n", total_time / 100);
        }
    return 0;
}