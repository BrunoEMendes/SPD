#include "pthread_arg_struct.h"

PthreadArg pthreadArg(int pthread_number, char* input, long * output_pthread, int pos, int odd, int run_till, int max_run, int start_number)
{
    PthreadArg result;
    result.pthread_number = pthread_number;
    result.input = input;
    result.output_pthread = output_pthread;
    result.pos = pos;
    result.odd = odd;
    result.run_till = run_till;
    result.max_run = max_run;
    result.start_number = start_number;
    return result;
}

