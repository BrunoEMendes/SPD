#ifndef OPEN_MP_H
#define OPEN_MP_H
#include "f_function.h"
#include "open_mp.h"
void add_to_array_openmp(long number, int div);
void factorials_loop(Function * f_array, char * input_string, long number,\
                                long max_number, int jump);
void run_openmp(Function *f_array, char *input_string);
void test_openMP(char * input_string);
#endif