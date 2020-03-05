#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "open_mp.h"
#include "sort.h"


omp_lock_t writelock;
long * open_mp_result;
int open_mp_size;

void add_to_array_openmp(long number, int div)
{
    // #pragma omp critical
    // {
    omp_init_lock(&writelock);
    open_mp_result[open_mp_size++] = div;
    long temp = number / div;
    if(div != temp)
        open_mp_result[open_mp_size++] = number / div;
    // }
    omp_unset_lock(&writelock);
}

void factorials_loop(Function * f_array, char * input_string, long number,\
                                long max_number, int jump)
{
    int temp = 0;
    #pragma omp parallel for
    for(long i = 3; i <= max_number; i += jump)
    {
        if(i > 10 || i ==8 || i!=7)
        {
            if(is_divisible_by_anything_else(input_string, i) == 1)
                add_to_array_openmp(number, i);
        }
        else if(i < 11 && has_pre_def_function(i, f_array))
        {
            temp = func_array_get(i, f_array);
            if(f_array[temp].func(input_string) == 1)
                add_to_array_openmp(number, i);
        }
    }
}

void run_openmp(Function *f_array, char *input_string)
{
    long number =  (long) strtol(input_string, (char **)NULL, 10);

    open_mp_size = 0;

    add_to_array_openmp(number, 1);
    long max_number = (long)sqrt(number);

    int is_pair = is_divisible_by_2(input_string);

    if(is_pair == 0)
        factorials_loop(f_array, input_string, number, max_number, 2);
    else
    {
        add_to_array_openmp(number, 2);
        factorials_loop(f_array, input_string, number, max_number, 1);
    }
}



void test_openMP(char * input_string)
{


    double elapsed_start, elapsed_merge, get_function_run_time();

    int size = sqrt((long) strtol(input_string, (char **)NULL, 10)) * 2;
    if(size > 500)
        size = sqrt((long) strtol(input_string, (char **)NULL, 10));
    open_mp_result= calloc( size, sizeof *open_mp_result);

    // function array
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};

    // omp lock init
    omp_init_lock(&writelock);



    if(time_output == 1)
        elapsed_start=get_function_run_time();

    run_openmp(f_array, input_string);

    omp_destroy_lock(&writelock);

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    sort_function(open_mp_result, open_mp_size);


    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);


    if(print_output == 1)
        print_factors(open_mp_result, open_mp_size);

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);

    open_mp_size = 0;
    free(open_mp_result);
}