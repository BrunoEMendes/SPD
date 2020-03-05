#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>

#include "sort.h"
#include "main.h"
#include "pthreads_2.h"
#include "pthreads_3.h"


// pthread that checks if its divisible by an even number
void * pthread_p_thread_divide_by_anything_even(void *arg)
{
    char * s = (char *) arg;
    long number =  (int) strtol(s, (char **)NULL, 10);
    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    int is_pair = is_divisible_by_2(s);
    int res = 14;
    int count = 0;
    if(is_pair == 1)
    {
        for(int i = 8; i < (int)sqrt(atoi(s)); i += 2)
            if((i != 10  && i != 9) && is_divisible_by_anything_else(s, i) == 1)
            {
                res = add_to_array(number, i, res, pthread_result);
                count++;
            }
    }
    res -=14 + count;
    pthread_exit(  (void*)res);
}

// pthread that checks if its divisible by an odd number
void * pthread_p_thread_divide_by_anything_odd(void *arg)
{
    char * s = (char *) arg;
    long number =  (int) strtol(s, (char **)NULL, 10);
    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    int is_pair = is_divisible_by_2(s);
    int start = 14 + ( (size - 14) /  2  + 1);
    int res = 14 + ( (size - 14) /  2  + 1) ;
    int count = 0;

    for(int i = 7; i < (int)sqrt(atoi(s)) + 2; i += 2)
        if((i != 10  && i != 9) && is_divisible_by_anything_else(s, i) == 1)
            res = add_to_array(number, i, res, pthread_result);
    res -= start;
    pthread_exit(  (void*)res);
}



void pthread_default_with_3_threads(char *s)
{

    double elapsed_start, elapsed_merge, get_function_run_time();

    if(time_output == 1)
        elapsed_start=get_function_run_time();

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));

    pthread_result = calloc(size, sizeof *pthread_result);

    pthread_t threads[3];
    void *size_array_thread_1;
    void *size_array_thread_2;
    void *size_array_thread_3;

    pthread_create(&threads[0], NULL, p_thread_default_function, (void *)s);
    pthread_create(&threads[1], NULL, pthread_p_thread_divide_by_anything_even, (void *)s);
    pthread_create(&threads[2], NULL, pthread_p_thread_divide_by_anything_odd, (void *)s);
    pthread_join(threads[0], &size_array_thread_1);
    pthread_join(threads[1], &size_array_thread_2);
    pthread_join(threads[2], &size_array_thread_3);
    int n = (int)size_array_thread_1 + (int)size_array_thread_2 + (int) size_array_thread_3;
    // printf("here %d %d %d\n", (int)size_array_thread_1, (int)size_array_thread_2,(int) size_array_thread_3);

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    sort_function(pthread_result, size);


    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = 0; i <= size ; i++)
            if(pthread_result[i] != 0)
                printf("%ld\n", pthread_result[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);

}
