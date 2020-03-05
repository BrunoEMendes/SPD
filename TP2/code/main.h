
#ifndef MAIN_H
#define MAIN_H

#include "division_function.h"

#define NUM_THREADS 4

extern int print_output;
extern int time_output;
extern int merge_sort;
extern int i_sort;
extern int q_sort;
typedef int (*f)(char * s);

/*
* structure type item
* has a number
* has a function associated to it
*/
typedef struct
{
    int res;
    f func;
}Function;


extern long * pthread_result;
extern int pthread_size[NUM_THREADS];

#endif