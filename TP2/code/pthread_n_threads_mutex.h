#ifndef PTHREAD_N_THREADS_MUTEX_H
#define PTHREAD_N_THREADS_MUTEX_H
long add_to_array_mutex(long number, long div,  long res, long * output);
void run_pthread(Function *f_array,long number, long* output, char * input_string, int pthread_number, long max_number, int jump);
void *pthread_find_factors_with_mutex(void * pa);
void pthread_with_mutex(char * input_string);
#endif