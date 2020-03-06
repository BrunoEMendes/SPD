#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"


#include "sort.h"
#include "main.h"
#include "f_function.h"
#include "sequential_no_optimization.h"


int sequential_output(char *input_string, int size, long * output)
{

    // couldnt make this global, apparently c doesnt allow to give structures values ??? probably there is input_string way arround this idk
    // TODO MAKE IT BETTER!
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};
    int res = 0;
    output[res++] = 1;
    output[res++] = strtol(input_string, (char **)NULL, 10);
    int pos;
    long number = strtol(input_string, (char **)NULL, 10);
    long number_sqrt = sqrt(number);
    for(int i = 2; i < size; i++)
    {
        // printf("here array %d\n", sizeof(output)/sizeof(output[0]));
        if(has_pre_def_function(i, f_array))
        {

            pos = func_array_get(i, f_array);

            if(f_array[pos].func(input_string) == 1)
            {
                output[res++] = f_array[pos].res;
                output[res++] = number / f_array[pos].res;
            }
        }
        else if(is_divisible_by_anything_else_number(number, i) == 1)
        {

            output[res++] = i;
            output[res++] = (int) strtol(input_string, (char **)NULL, 10) / i;
        }

    }
    return res;
}

//main function sequential without optimization
void sequential_default(char * input_string)
{
    int size = sqrt((int) strtol(input_string, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(input_string, (char **)NULL, 10));
    long output [size];

    double elapsed_start, elapsed_merge, get_function_run_time();

    if(time_output == 1)
        elapsed_start=get_function_run_time();


    int n = sequential_output(input_string, size, output);

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


