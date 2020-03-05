#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "main.h"
#include "sort.h"
#include "f_function.h"
#include "pthreads_2.h"


// pthread that checks if its divisible by even or an odd number
void * p_thread_divide_by_anything(void *arg)
{
    char * s = (char *) arg;
    long number =  (int) strtol(s, (char **)NULL, 10);

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    int is_pair = is_divisible_by_2(s);
    int res = 14; // because its the maximum of options that a function that is divisible by all the 10 previous thingies
    if(is_pair == 1)
    {
        for(int i = 7; i < (int)sqrt(atoi(s)); i++)
            if((i != 10  && i != 9) && is_divisible_by_anything_else(s, i) == 1)
            {
                res = add_to_array(number, i, res, pthread_result);
            }
    }
    else
        for(int i = 7; i <= (int)sqrt(atoi(s)); i += 2)
        {
            if(i != 9 && is_divisible_by_anything_else(s, i) == 1 )
                res = add_to_array(number, i, res, pthread_result);
        }
    res -=14;
    pthread_exit(  (void*)res);
}


// uses the functions for 2, 3, 4, 5, 6, 9, 10
void * p_thread_default_function(void * arg)
{
    char * s = (char *) arg;
    int res = 0;

    long number =  (int) strtol(s, (char **)NULL, 10);
    int is_pair = is_divisible_by_2(s);
    pthread_result[res++] = 1;
    pthread_result[res++] = number;

    int number_sqrt = sqrt(number);
    if(2 <= number_sqrt && is_divisible_by_2(s) == 1)
    {
        is_pair = 1;
        res = add_to_array(number, 2, res, pthread_result);
        if(4  <= number_sqrt && is_divisible_by_4(s) == 1)
            res = add_to_array(number, 4, res, pthread_result);
    }
    if(3 <= number_sqrt &&is_divisible_by_3(s) == 1)
    {
        res = add_to_array(number, 3, res, pthread_result);
        if(6 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 6, res, pthread_result);
        if(9 <= number_sqrt && is_divisible_by_9(s) == 1)
            res = add_to_array(number, 9, res, pthread_result);
    }
    if(5 <= number_sqrt && is_divisible_by_5(s) == 1)
    {
        res = add_to_array(number, 5, res, pthread_result);
        if(10 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 10, res, pthread_result);
    }
    pthread_exit((void*)res);
}



void pthread_default(char *s)
{

    double elapsed_start, elapsed_merge, get_function_run_time();

    if(time_output == 1)
        elapsed_start=get_function_run_time();

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    pthread_result = calloc( size, sizeof *pthread_result);
    pthread_t threads[2];
    void *size_array_thread_1;
    void *size_array_thread_2;

    pthread_create(&threads[0], NULL, p_thread_default_function, (void *)s);
    pthread_create(&threads[1], NULL, p_thread_divide_by_anything, (void *)s);
    pthread_join(threads[0], &size_array_thread_1);
    pthread_join(threads[1], &size_array_thread_2);
    int n = (int)size_array_thread_1 + (int)size_array_thread_2;

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }


    sort_function(pthread_result, size + 1);


    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = size - n + 1; i <= size ; i++)
            printf("%ld\n", pthread_result[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
}