
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "main.h"
#include "sort.h"
#include "f_function.h"
#include "pthread_arg_struct.h"
#include "pthread_n_threads_mutex.h"


pthread_mutex_t lock;
long pthread_result_n = 0;
long * pthread_result;
int pthread_size[NUM_THREADS];


long add_to_array_mutex(long number, long div,  long res, long * output)
{
    pthread_mutex_lock(&lock);
    output[res++] = div;
    long temp = number / div;
    if(div != temp)
        output[res++] = number / div;
    pthread_mutex_unlock(&lock);
    return res;
}

void run_pthread(Function *f_array,long number, long* output, char * input_string, int pthread_number, long max_number, int jump)
{
    int temp = 0;
    for(long i = 1 + pthread_number; i <= max_number; i += NUM_THREADS)
    {

        if(i == 1)
            pthread_result_n  = add_to_array_mutex(number, i, pthread_result_n, output);
        else if(has_pre_def_function(i, f_array))
        {

            temp = func_array_get(i, f_array);
            if(f_array[temp].func(input_string) == 1)
                pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);

        }
        else if(is_divisible_by_anything_else_number(number, i) == 1)
            pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);
    }
}
void *pthread_find_factors_with_mutex(void * pa)
{
    PthreadArg *pArg = (PthreadArg *)pa;
    int pthread_number = pArg->pthread_number;
    long number =  (long) strtol(pArg->input, (char **)NULL, 10);
    char * input_string = pArg->input;
    // int pos = pArg->pos;
    int odd = pArg->odd;
    // int size = pArg->max_run;
    int next_pthread = pArg->run_till;
    long * output = pArg->output_pthread;
    int start_number = pArg->start_number;

    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};

    int temp = 0;
    if(odd == 1)
    {
        run_pthread(f_array, number, output, input_string, pthread_number, (long)sqrt(number), 2);
    }
    else
    {
        run_pthread(f_array, number, output, input_string, pthread_number, (long)sqrt(number), 1);
    }
    pthread_exit(NULL);
}


void pthread_with_mutex(char * input_string)
{
    double elapsed_start, elapsed_merge, get_function_run_time();

    int size = sqrt((int) strtol(input_string, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(input_string, (char **)NULL, 10));

    long *output_pthread= calloc( size, sizeof *output_pthread);;

    if(time_output == 1)
        elapsed_start=get_function_run_time();
    pthread_t threads[NUM_THREADS];
    PthreadArg pa[NUM_THREADS];
    // PthreadArg pthreadArg(int pthread_number, char* input, int * output_pthread, int pos, int odd, int run_till, int max_run, int start_number)
    int odd = is_divisible_by_2(input_string)  == 1 ? 0 : 1;
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        pa[i] = pthreadArg(i, input_string, output_pthread, i * (size / NUM_THREADS), odd, (i + 1) * (int)sqrt(atoi(input_string)) / NUM_THREADS, (i + 1) * (size / NUM_THREADS),i * (int)sqrt(atoi(input_string)) / NUM_THREADS );
    }

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        exit(0);
    }

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, pthread_find_factors_with_mutex, (void *) &pa[i]);

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);


    pthread_mutex_destroy(&lock);

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    sort_function(output_pthread, pthread_result_n);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = 0; i < pthread_result_n ; i++)
            printf("%ld\n", output_pthread[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
    pthread_result_n = 0;
    free(pthread_result);
}
