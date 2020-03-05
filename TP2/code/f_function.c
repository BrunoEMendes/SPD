#include "f_function.h"

f func_array[7] = {&is_divisible_by_2, &is_divisible_by_3, &is_divisible_by_4, &is_divisible_by_5, &is_divisible_by_6, &is_divisible_by_9, &is_divisible_by_10};
Function function(int n, f f)
{
    Function result;
    result.res = n;
    result.func = f;
    return result;
}

// trying to work arround with structures and array of functions and made something like an object

// couldnt make this as input_string has function java like
int has_pre_def_function(int n, Function * f_array)
{
    for(int i = 0; i < 7; i++)
        if(n == f_array[i].res)
            return 1;
    return 0;
}
// couldnt make this input_string getter function java like
int func_array_get(int n, Function *f_array)
{
    for(int i = 0; i < 7; i++)
        if (f_array[i].res == n)
            return i;
    return -1;
}
