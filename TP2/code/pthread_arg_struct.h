#ifndef PTHREAD_ARG_STRUCT_H
#define PTHREAD_ARG_STRUCT_H

typedef struct pthreadarg
{
    int pthread_number;
    char * input;
    long * output_pthread;
    int pos;
    int odd;
    int run_till;
    int max_run;
    int start_number;
}PthreadArg;

PthreadArg pthreadArg(int pthread_number, char* input, long * output_pthread, int pos, int odd, int run_till, int max_run, int start_number);

#endif