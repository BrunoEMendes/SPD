#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#include "sort.h"
#include "main.h"
#include "sequential_with_optimization.h"

// add value to array
int add_to_array(long number, long div,  int res, long * output)
{
    output[res++] = div;
    output[res++] = number / div;
    return res;
}

// sequential with optimization
int sequential_optimization_loop(char *input_string, int size, long * output)
{
    //if its divisible by two then it will run all the pair functions like 2 / 4 / 6 etc otherwise it wont
    int is_pair = 0;
    int res = 0;
    output[res++] = 1;
    output[res++] = (long) strtol(input_string, (char **)NULL, 10);

    long number =  (long) strtol(input_string, (char **)NULL, 10);
    long number_sqrt = sqrt(number);

    if(2 <= number_sqrt && is_divisible_by_2(input_string) == 1)
    {
        is_pair = 1;
        res = add_to_array(number, 2, res, output);
        if(4  <= number_sqrt && is_divisible_by_4(input_string) == 1)
            res = add_to_array(number, 4, res, output);
    }
    if(3 <= number_sqrt &&is_divisible_by_3(input_string) == 1)
    {
        res = add_to_array(number, 3, res, output);
        if(6 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 6, res, output);
        if(9 <= number_sqrt && is_divisible_by_9(input_string) == 1)
            res = add_to_array(number, 9, res, output);
    }
    if(5 <= number_sqrt && is_divisible_by_5(input_string) == 1)
    {
        res = add_to_array(number, 5, res, output);
        if(10 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 10, res, output);
    }
    if(is_pair == 1)
    {
        for(long i = 7; i <= number_sqrt; i++)
        {
            if((i != 10  && i != 9) && is_divisible_by_anything_else_number(number, i) == 1)
                res = add_to_array(number, i, res, output);
        }
    }
    else
        for(long i = 7; i <= number_sqrt; i += 2)
        {
            if(i != 9 && is_divisible_by_anything_else_number(number, i) == 1 )
                res = add_to_array(number, i, res, output);
        }
    return res;
}

/**
 *
 *
 * sequential with optimization
 */
void sequential_optimization(char *input_string)
{
    long size = sqrt((long) strtol(input_string, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(input_string, (char **)NULL, 10));
    long output [size];

    double elapsed_start, elapsed_merge, get_function_run_time();

    if(time_output == 1)
        elapsed_start=get_function_run_time();

    int n = sequential_optimization_loop(input_string, size, output);

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }
    sort_function(output, n);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        print_factors(output, n, input_string);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
}