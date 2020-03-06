
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "main.h"
#include "sort.h"
#include "f_function.h"
#include "pthread_arg_struct.h"
#include "pthreads_n_threads.h"


long * pthread_result;
int pthread_size[NUM_THREADS];


void *generic_function(void * pa)
{

    PthreadArg *pArg = (PthreadArg *)pa;
    // int pthread_number = pArg->pthread_number;
    long number =  (long) strtol(pArg->input, (char **)NULL, 10);
    char * input_string = pArg->input;
    int pos = pArg->pos;
    int odd = pArg->odd;
    // int size = pArg->max_run;
    int next_pthread = pArg->run_till;
    long * output = pArg->output_pthread;
    int start_number = pArg->start_number;
    int res = pos;
    // for(int i = 0; i < NUM_THREADS; ++i)
    // printf("%d %ld %d %d %d %d %d\n", pthread_number, number, pos, odd, size, next_pthread, start_number);
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};

    int temp = 0;
    if(odd == 1)
    {
        for(int i = start_number + 1; i <= next_pthread; i += 2)
        {
            if(i == 1)
                res = add_to_array(number, i, res, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    res = add_to_array(number, i, res, output);

            }
            else if(is_divisible_by_anything_else_number(number, i) == 1){
                res = add_to_array(number, i, res, output);
            }
        }
    }
    else
    {
        for(int i = start_number + 1; i <= next_pthread; i ++)
        {
            if(i == 1)
                res = add_to_array(number, i, res, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    res = add_to_array(number, i, res, output);

            }
            else if(is_divisible_by_anything_else_number(number, i) == 1)
                res = add_to_array(number, i, res, output);
        }
    }
    res -= pos;
    pthread_exit((void *)res);
}

void pthread_optimzation_with_custom_number_of_threads(char *s)
{
    double elapsed_start, elapsed_merge, get_function_run_time();

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));

    long *output_pthread= calloc( size, sizeof *output_pthread);;

    void * size_array_thread[NUM_THREADS];

    if(time_output == 1)
        elapsed_start=get_function_run_time();
    pthread_t threads[NUM_THREADS];
    PthreadArg pa[NUM_THREADS];
    // PthreadArg pthreadArg(int pthread_number, char* input, int * output_pthread, int pos, int odd, int run_till, int max_run, int start_number)
    int odd = is_divisible_by_2(s)  == 1 ? 0 : 1;
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        pa[i] = pthreadArg(i, s, output_pthread, i * (size / NUM_THREADS), odd, (i + 1) * (int)sqrt(atoi(s)) / NUM_THREADS, (i + 1) * (size / NUM_THREADS),i * (int)sqrt(atoi(s)) / NUM_THREADS );
    }

    // for(int i = 0; i < NUM_THREADS; ++i)
    //     printf("%d %s %d %d %d %d\n", pa[i].pthread_number,pa[i].input, pa[i].pos, pa[i].odd, pa[i].run_till, pa[i].max_run);

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, generic_function, (void *) &pa[i]);
    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], &size_array_thread[i]);
    int size_of_output = 0;
    for(int i = 0; i < NUM_THREADS; i++)
        size_of_output += (int)size_array_thread[i];


    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    sort_function(output_pthread, size);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = size - size_of_output; i < size ; i++)
            if(output_pthread[i] != 0)
                printf("%ld\n", output_pthread[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
    free(pthread_result);
}