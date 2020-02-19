#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#define NUM_THREADS 4
#define foreach( ptrvar, strvar, n) char ** ptrvar; for( ptrvar = strvar ;ptrvar < (ptrvar + n); *ptrvar++)

// variáveis globais que definem se vai existir print de output, tempo, e define qual funçao de sort se utiliza
int print_output =  0;
int time_output = 0;
int merge_sort = 0;
int i_sort = 0;
int q_sort = 0;

/**
* função de comparação do qSort
* void * a -> item a comparar
* void * b -> item a comparar
*/
int cmpfunc (const void * a, const void * b) {
    return ( *(long *)a - * (long *)b );
}
//------------------------- isort ref: https://www.geeksforgeeks.org/insertion-sort/ --------------------------------------------------------
/* Function to sort an array using insertion sort*/
void insertionSort(long arr[], int n)
{
    int i, j;
    long key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// ----------------------end of isort-------------------------------------------------------------------------------------------------------------
//---------------------- merge sort ref:https://www.geeksforgeeks.org/merge-sort/ ----------------------------------------------------------------
void merge(long arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    long L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(long arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
//----------------end merge sort----------------------------

// função de tempo implementada pela Professora Margarida Moura em SPD
// https://tutoria.ualg.pt/2019/pluginfile.php/132032/mod_resource/content/0/Guia1-Exerc%C3%ADcios%20Iniciais.pdf
double get_function_run_time()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return ( (double)(time.tv_sec*1000000+time.tv_usec)/1000000 );
}

// função do professor Pedro Guerreiro de PI 2019/2020
//https://tutoria.ualg.pt/2019/pluginfile.php/116217/mod_resource/content/12/our_strings.c
char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

// gets last char of input_string string and converts it to int
int get_last_digit(char * s)
{
    return s[strlen(s) - 1] - '0';
}
// gets penultimate digit
int get_last_two_digits(char * s)
{
    assert(strlen(s) > 1);
    return (s[strlen(s) - 2] - '0') * 10 + get_last_digit(s);
}

// sums the digits
char * sum_digits(char * s)
{
    char * res = malloc(strlen(s) * sizeof(char));
    int sum = 0;
    for(int i = 0; i < strlen(s); ++i)
        if(s[i] >= '0' && s[i] <= '9')
            sum += (s[i] - '0');
    sprintf(res, "%d", sum);
    return res;
}


// counts the total of digits
char * count_digits(char * s)
{
    char * res = malloc(12);
    int sum = 0;
    for(int i = 0; i < strlen(s); ++i)
        if(s[i] > '0' && s[i] <= '9')
            sum ++;
    sprintf(res, "%d", sum);
    return res;
}

// checks if its divisible by_2
int is_divisible_by_2(char * s)
{
    return get_last_digit(s) % 2 == 0;
}

// check if its divisible by 3
int is_divisible_by_3(char * s)
{
    char * count = count_digits(s);
    char * sum = str_dup(s);
    char * free_me;
    do
    {
        free_me = sum;
        sum = sum_digits(sum);
        free(free_me);
        free_me = count;
        count = count_digits(sum);
        free(free_me);
    } while (atoi(count) > 1);
    int n = atoi(sum);
    int res = n == 3 || n == 6 || n == 9;
    free(sum);
    free(count);
    return res;
}

// check if its divisible by 4
// TODO
// gotta find better solution
int is_divisible_by_4(char *s)
{
    int n = get_last_digit(s);
    if(is_divisible_by_2(s))
    {
        if(strlen(s) > 1)
            return get_last_two_digits(s) % 4 == 0;
        else
            return n == 4 || n == 8;
    }
    else
        return 0;
}

// check if its divisible by 5
int is_divisible_by_5(char * s)
{
    int n = get_last_digit(s);
    return n == 5 || n == 0;
}

// check if its divisible by 6
int is_divisible_by_6(char * s)
{
    return is_divisible_by_2(s) && is_divisible_by_3(s);
}

int is_divisible_by_9(char * s)
{
    char * count = count_digits(s);
    char * sum = str_dup(s);
    char * free_me;
    do
    {
        free_me = sum;
        sum = sum_digits(sum);
        free(free_me);
        free_me = count;
        count = count_digits(sum);
        free(free_me);
    } while (atoi(count) > 1);
    int n = atoi(sum);
    int res = n == 9;
    free(sum);
    free(count);
    return res;
}

// ------------------------------ FUNÇÕES FACTORIAIS -----------------------------------------
// check if its divisible by 10
int is_divisible_by_10(char * s)
{
    return get_last_digit(s) == 0;
}

//if two and 5 are divisible
int is_divisible_by_10_2_5(int two, int five)
{
    return two && five;
}

int is_divisible_by_anything_else(char *s, int n)
{
    return atoi(s) % n == 0;
}

// prints array Strings (testing purposes)
void print_string_array(char ** input_string, int n)
{
    foreach(p1, input_string, n)
        printf("%s\n", *p1);
}

// prints the factors
void print_factors(long * input_string, int n, char * factor)
{
    printf("Factors\n");
    for(int i = 0; i < n; i++)
        printf("%ld\n", input_string[i]);
}

// trying to work arround with structures and array of functions and made something like an object
typedef int (*f)(char * s);

/*
* structure type item
* has a number
* has a function associated to it
*/
typedef struct Function
{
    int res;
    f func;
}Function;

/*
* constructor Function
*/
Function function(int n, f f)
{
    Function result;
    result.res = n;
    result.func = f;
    return result;
}

//array de funções
f func_array[7] = {&is_divisible_by_2, &is_divisible_by_3, &is_divisible_by_4, &is_divisible_by_5, &is_divisible_by_6, &is_divisible_by_9, &is_divisible_by_10};

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

// end of testing zone
//----------------------------------------------------SEQUENTIAL------------------------------------------------------------------------------------------

int sequential_output(char *input_string, int size, long * output)
{
    // couldnt make this global, apparently c doesnt allow to give structures values ??? probably there is input_string way arround this idk
    // TODO MAKE IT BETTER!
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};
    int res = 0;
    output[res++] = 1;
    output[res++] = (int) strtol(input_string, (char **)NULL, 10);
    int pos;
    long number =  (int) strtol(input_string, (char **)NULL, 10);

    for(int i = 2; i < size; i++)
    {
        if(has_pre_def_function(i, f_array))
        {
            pos = func_array_get(i, f_array);
            if(f_array[pos].func(input_string) == 1)
            {
                output[res++] = f_array[pos].res;
                output[res++] = number / f_array[pos].res;
            }
        }
        else if(is_divisible_by_anything_else(input_string, i) == 1)
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

    if(merge_sort == 1)
        mergeSort(output, 0, n - 1);
    if(i_sort == 1)
        insertionSort(output, n);
    if(q_sort == 1)
        qsort(output, n, sizeof(long),cmpfunc);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        print_factors(output, n, input_string);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);

}

// add value to array
int add_to_array(long number, int div,  int res, long * output)
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
    output[res++] = (int) strtol(input_string, (char **)NULL, 10);

    long number =  (int) strtol(input_string, (char **)NULL, 10);
    int number_sqrt = sqrt(number);
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
        for(int i = 7; i <= size; i++)
            if((i != 10  && i != 9) && is_divisible_by_anything_else(input_string, i) == 1)
            {
                res = add_to_array(number, i, res, output);
            }
    }
    else
        for(int i = 7; i < size; i += 2)
        {
            if(i != 9 && is_divisible_by_anything_else(input_string, i) == 1 )
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
    int size = sqrt((int) strtol(input_string, (char **)NULL, 10)) * 2;
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

    if(merge_sort == 1)
        mergeSort(output, 0, n - 1);
    if(i_sort == 1)
        insertionSort(output, n);
    if(q_sort == 1)
        qsort(output, n, sizeof(long),cmpfunc);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        print_factors(output, n, input_string);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
}

//----------------------------------------------------PTHREADS------------------------------------------------------------------------------------------


//test with 2 threads
long * pthread_result;
int pthread_size[NUM_THREADS];

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

// pthread that checks if its divisible by even or an odd number
void * p_thread_divide_by_anything(void *arg)
{
    char * s = (char *) arg;
    long number =  (int) strtol(s, (char **)NULL, 10);

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    int is_pair = is_divisible_by_2(s);
    int res = 14; // because its the maximum of options that a function that is divisible by all the 10 previous thingies
    if(is_pair == 1)
    {
        for(int i = 7; i < (int)sqrt(atoi(s)); i++)
            if((i != 10  && i != 9) && is_divisible_by_anything_else(s, i) == 1)
            {
                res = add_to_array(number, i, res, pthread_result);
            }
    }
    else
        for(int i = 7; i <= (int)sqrt(atoi(s)); i += 2)
        {
            if(i != 9 && is_divisible_by_anything_else(s, i) == 1 )
                res = add_to_array(number, i, res, pthread_result);
        }
    res -=14;
    pthread_exit(  (void*)res);
}

// uses the functions for 2, 3, 4, 5, 6, 9, 10
void * p_thread_default_function(void * arg)
{
    char * s = (char *) arg;
    int res = 0;

    long number =  (int) strtol(s, (char **)NULL, 10);
    int is_pair = is_divisible_by_2(s);
    pthread_result[res++] = 1;
    pthread_result[res++] = number;

    int number_sqrt = sqrt(number);
    if(2 <= number_sqrt && is_divisible_by_2(s) == 1)
    {
        is_pair = 1;
        res = add_to_array(number, 2, res, pthread_result);
        if(4  <= number_sqrt && is_divisible_by_4(s) == 1)
            res = add_to_array(number, 4, res, pthread_result);
    }
    if(3 <= number_sqrt &&is_divisible_by_3(s) == 1)
    {
        res = add_to_array(number, 3, res, pthread_result);
        if(6 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 6, res, pthread_result);
        if(9 <= number_sqrt && is_divisible_by_9(s) == 1)
            res = add_to_array(number, 9, res, pthread_result);
    }
    if(5 <= number_sqrt && is_divisible_by_5(s) == 1)
    {
        res = add_to_array(number, 5, res, pthread_result);
        if(10 <= number_sqrt && is_pair == 1)
            res = add_to_array(number, 10, res, pthread_result);
    }
    pthread_exit((void*)res);
}

// pthread function that uses 3 pthreads
// pthread fot he default functions -> 2, 3, 4, 5, 6, 9, 10
// pthread for even numbers
// pthread for odd numbers


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
    long rc, t;
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

    if(merge_sort == 1)
        mergeSort(pthread_result, 0, size);
    if(i_sort == 1)
        insertionSort(pthread_result, size);
    if(q_sort == 1)
        qsort(pthread_result, size, sizeof(long),cmpfunc);

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

void pthread_default(char *s)
{

    double elapsed_start, elapsed_merge, get_function_run_time();

    if(time_output == 1)
        elapsed_start=get_function_run_time();

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));
    pthread_result = calloc( size, sizeof *pthread_result);
    pthread_t threads[2];
    long rc, t;
    void *size_array_thread_1;
    void *size_array_thread_2;

    pthread_create(&threads[0], NULL, p_thread_default_function, (void *)s);
    pthread_create(&threads[1], NULL, p_thread_divide_by_anything, (void *)s);
    pthread_join(threads[0], &size_array_thread_1);
    pthread_join(threads[1], &size_array_thread_2);
    int n = (int)size_array_thread_1 + (int)size_array_thread_2;

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    if(merge_sort == 1)
        mergeSort(pthread_result, 0, size);
    if(i_sort == 1)
        insertionSort(pthread_result, size);
    if(q_sort == 1)
        qsort(pthread_result, size, sizeof(long),cmpfunc);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = size - n + 1; i <= size ; i++)
            printf("%ld\n", pthread_result[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
}
//--------------------------------------N THREADS_--------------------------------------------------------------------------

//--------------------------------------- STRUCUTRE FOR THREADS-------------------------------------------------------------------
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
//--------------------------------------- END OF STRUCUTRE FOR THREADS-------------------------------------------------------------------

void *generic_function(void * pa)
{

    PthreadArg *pArg = (PthreadArg *)pa;
    int pthread_number = pArg->pthread_number;
    long number =  (int) strtol(pArg->input, (char **)NULL, 10);
    char * input_string = pArg->input;
    int pos = pArg->pos;
    int odd = pArg->odd;
    int size = pArg->max_run;
    int next_pthread = pArg->run_till;
    long * output = pArg->output_pthread;
    int start_number = pArg->start_number;

    int res = pos;
    // for(int i = 0; i < NUM_THREADS; ++i)
    // printf("%d %ld %d %d %d %d %d\n", pthread_number, number, pos, odd, size, next_pthread, start_number);
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};


    int temp = 0;
    if(odd == 1)
    {
        for(int i = start_number + 1; i <= next_pthread; i += 2)
        {
            if(i == 1)
                res = add_to_array(number, i, res, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    res = add_to_array(number, i, res, output);

            }
            else if(is_divisible_by_anything_else(input_string, i) == 1){
                res = add_to_array(number, i, res, output);
            }
        }
    }
    else
    {
        for(int i = start_number + 1; i <= next_pthread; i ++)
        {
            if(i == 1)
                res = add_to_array(number, i, res, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    res = add_to_array(number, i, res, output);

            }
            else if(is_divisible_by_anything_else(input_string, i) == 1)
                res = add_to_array(number, i, res, output);
        }
    }
    res -= pos;
    pthread_exit((void *)res);
}

void pthread_optimzation_with_custom_number_of_threads(char *s)
{
    double elapsed_start, elapsed_merge, get_function_run_time();

    int size = sqrt((int) strtol(s, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(s, (char **)NULL, 10));

    long *output_pthread= calloc( size, sizeof *output_pthread);;

    void * size_array_thread[NUM_THREADS];

    if(time_output == 1)
        elapsed_start=get_function_run_time();
    pthread_t threads[NUM_THREADS];
    PthreadArg pa[NUM_THREADS];
    // PthreadArg pthreadArg(int pthread_number, char* input, int * output_pthread, int pos, int odd, int run_till, int max_run, int start_number)
    int odd = is_divisible_by_2(s)  == 1 ? 0 : 1;
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        pa[i] = pthreadArg(i, s, output_pthread, i * (size / NUM_THREADS), odd, (i + 1) * (int)sqrt(atoi(s)) / NUM_THREADS, (i + 1) * (size / NUM_THREADS),i * (int)sqrt(atoi(s)) / NUM_THREADS );
    }

    // for(int i = 0; i < NUM_THREADS; ++i)
    //     printf("%d %s %d %d %d %d\n", pa[i].pthread_number,pa[i].input, pa[i].pos, pa[i].odd, pa[i].run_till, pa[i].max_run);

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, generic_function, (void *) &pa[i]);

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], &size_array_thread[i]);
    int size_of_output = 0;
    for(int i = 0; i < NUM_THREADS; i++)
        size_of_output += (int)size_array_thread[i];


    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    if(merge_sort == 1)
        mergeSort(output_pthread, 0, size);
    if(i_sort == 1)
        insertionSort(output_pthread, size);
    if(q_sort == 1)
        qsort(output_pthread, size, sizeof(long),cmpfunc);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = size - size_of_output; i < size ; i++)
            if(output_pthread[i] != 0)
                printf("%ld\n", output_pthread[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
    free(pthread_result);
}
// ------------------------------------------------WITH MUTEXES---------------------------------------------------------------------------

pthread_mutex_t lock;
int pthread_result_n = 0;


int add_to_array_mutex(long number, int div,  int res, long * output)
{
    pthread_mutex_lock(&lock);
    output[res++] = div;
    int temp = number / div;
    if(div != temp)
        output[res++] = number / div;
    pthread_mutex_unlock(&lock);
    return res;
}

void *pthread_find_factors_with_mutex(void * pa)
{
    PthreadArg *pArg = (PthreadArg *)pa;
    int pthread_number = pArg->pthread_number;
    long number =  (int) strtol(pArg->input, (char **)NULL, 10);
    char * input_string = pArg->input;
    int pos = pArg->pos;
    int odd = pArg->odd;
    int size = pArg->max_run;
    int next_pthread = pArg->run_till;
    long * output = pArg->output_pthread;
    int start_number = pArg->start_number;

    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};


    int temp = 0;
    if(odd == 1)
    {
        for(int i = start_number + 1; i <= next_pthread; i += 2)
        {
            if(i == 1)
                pthread_result_n  = add_to_array_mutex(number, i, pthread_result_n, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);

            }
            else if(is_divisible_by_anything_else(input_string, i) == 1)
                pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);
        }
    }
    else
    {
        for(int i = start_number + 1; i <= next_pthread; i ++)
        {
            if(i == 1)
                pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);
            else if(has_pre_def_function(i, f_array))
            {
                temp = func_array_get(i, f_array);
                if(f_array[temp].func(input_string) == 1)
                    pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);

            }
            else if(is_divisible_by_anything_else(input_string, i) == 1)
                pthread_result_n = add_to_array_mutex(number, i, pthread_result_n, output);
        }
    }
    pthread_exit(NULL);
}


void pthread_with_mutex(char * input_string)
{
    double elapsed_start, elapsed_merge, get_function_run_time();

    int size = sqrt((int) strtol(input_string, (char **)NULL, 10)) * 2;
    if(size < 500)
        size += size % NUM_THREADS;
    else
        size = sqrt((int) strtol(input_string, (char **)NULL, 10));

    long *output_pthread= calloc( size, sizeof *output_pthread);;

    if(time_output == 1)
        elapsed_start=get_function_run_time();
    pthread_t threads[NUM_THREADS];
    PthreadArg pa[NUM_THREADS];
    // PthreadArg pthreadArg(int pthread_number, char* input, int * output_pthread, int pos, int odd, int run_till, int max_run, int start_number)
    int odd = is_divisible_by_2(input_string)  == 1 ? 0 : 1;
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        pa[i] = pthreadArg(i, input_string, output_pthread, i * (size / NUM_THREADS), odd, (i + 1) * (int)sqrt(atoi(input_string)) / NUM_THREADS, (i + 1) * (size / NUM_THREADS),i * (int)sqrt(atoi(input_string)) / NUM_THREADS );
    }

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, pthread_find_factors_with_mutex, (void *) &pa[i]);

    for(int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);


    pthread_mutex_destroy(&lock);

    if(time_output == 1)
    {
        elapsed_merge = get_function_run_time();
        printf( "\nElapsed time till sort : Loop time = %8f\n", elapsed_merge - elapsed_start);
    }

    if(merge_sort == 1)
        mergeSort(output_pthread, 0, pthread_result_n);
    if(i_sort == 1)
        insertionSort(output_pthread, pthread_result_n);
    if(q_sort == 1)
        qsort(output_pthread, pthread_result_n, sizeof(long),cmpfunc);

    if(time_output == 1)
        printf( "\nElapsed time after sort : Loop time = %8f\n", get_function_run_time() - elapsed_merge);

    if(print_output == 1)
    {
        for(int i = 0; i < pthread_result_n ; i++)
            printf("%ld\n", output_pthread[i]);
    }

    if(time_output == 1)
        printf( "\nElapsed time: Loop time = %8f\n", get_function_run_time() - elapsed_start);
    pthread_result_n = 0;
    free(pthread_result);
}
// ---------------------------------------------------- UNIT TEST SECTION -----------------------------------------------------------------------------

void unit_tests_array_of_functions(void)
{
    Function f_array[7]= {function(2, &is_divisible_by_2), function(3, &is_divisible_by_3), function(4, &is_divisible_by_4),
    function(5, &is_divisible_by_5), function(6, &is_divisible_by_6), function(9, &is_divisible_by_9), function(10, &is_divisible_by_10)};
    char * str_array[7] = {"11000","200", "20001", "200111", "200032", "234112341234", "12340123419234"};

    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 7; ++j)
            printf("is divisible %s by %d? res: %d\n",str_array[i], f_array[j].res, f_array[j].func(str_array[i]));
}

void unit_tests_is_divisible_by_anything_else(void)
{
    char * test_number_1 = "500";
    assert(is_divisible_by_anything_else(test_number_1, 7) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 8) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 11) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 12) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 13) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 14) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 15) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 16) == 0);
    assert(is_divisible_by_anything_else(test_number_1, 50) == 1);
    printf("unit_tests_is_divisible_by_anything_else works\n");
}

void unit_tests_is_divisible_by_10(void)
{
    char * test_number_1 = "0";
    char * test_number_2 = "10";
    char * test_number_3 = "5";
    char * test_number_4 = "15";
    char * test_number_5 = "1005";
    char * test_number_6 = "50";
    char * test_number_7 = "12";
    char * test_number_8 = "10001";
    assert(is_divisible_by_10(test_number_1) == 1);
    assert(is_divisible_by_10(test_number_2) == 1);
    assert(is_divisible_by_10(test_number_3) == 0);
    assert(is_divisible_by_10(test_number_4) == 0);
    assert(is_divisible_by_10(test_number_5) == 0);
    assert(is_divisible_by_10(test_number_6) == 1);
    assert(is_divisible_by_10(test_number_7) == 0);
    assert(is_divisible_by_10(test_number_8) == 0);
    printf("unit_tests_is_divisible_by_10 works\n");
}

void unit_tests_is_divisible_by_9(void)
{
    char * test_number_1 = "120";
    char * test_number_2 = "9";
    char * test_number_3 = "12";
    char * test_number_4 = "24";
    char * test_number_5 = "100";
    char * test_number_6 = "180";
    char * test_number_7 = "108";
    char * test_number_8 = "10008";
    char * test_number_9 = "1007";
    assert(is_divisible_by_9(test_number_1) == 0);
    assert(is_divisible_by_9(test_number_2) == 1);
    assert(is_divisible_by_9(test_number_3) == 0);
    assert(is_divisible_by_9(test_number_4) == 0);
    assert(is_divisible_by_9(test_number_5) == 0);
    assert(is_divisible_by_9(test_number_6) == 1);
    assert(is_divisible_by_9(test_number_7) == 1);
    assert(is_divisible_by_9(test_number_8) == 1);
    assert(is_divisible_by_9(test_number_9) == 0);
    printf("unit_tests_is_divisible_by_9 works\n");
}

void unit_tests_is_divisible_by_6(void)
{
    char * test_number_1 = "3";
    char * test_number_2 = "6";
    char * test_number_3 = "12";
    char * test_number_4 = "2000";
    char * test_number_5 = "102030";
    char * test_number_6 = "1111";
    char * test_number_7 = "99";
    char * test_number_8 = "60";
    assert(is_divisible_by_6(test_number_1) == 0);
    assert(is_divisible_by_6(test_number_2) == 1);
    assert(is_divisible_by_6(test_number_3) == 1);
    assert(is_divisible_by_6(test_number_4) == 0);
    assert(is_divisible_by_6(test_number_5) == 1);
    assert(is_divisible_by_6(test_number_6) == 0);
    assert(is_divisible_by_6(test_number_7) == 0);
    assert(is_divisible_by_6(test_number_8) == 1);
    printf("unit_tests_is_divisible_by_6 works\n");
}

void unit_tests_is_divisible_by_5(void)
{
    char * test_number_1 = "0";
    char * test_number_2 = "5";
    char * test_number_3 = "10";
    char * test_number_4 = "11";
    char * test_number_5 = "20001";
    char * test_number_6 = "2005";
    char * test_number_7 = "201";
    char * test_number_8 = "1001101";
    assert(is_divisible_by_5(test_number_1) == 1);
    assert(is_divisible_by_5(test_number_2) == 1);
    assert(is_divisible_by_5(test_number_3) == 1);
    assert(is_divisible_by_5(test_number_4) == 0);
    assert(is_divisible_by_5(test_number_5) == 0);
    assert(is_divisible_by_5(test_number_6) == 1);
    assert(is_divisible_by_5(test_number_7) == 0);
    assert(is_divisible_by_5(test_number_8) == 0);
    printf("unit_tests_is_divisible_by_5 works\n");
}


void unit_tests_is_divisible_by_4(void)
{
    char * test_number_1 = "4";
    char * test_number_2 = "8";
    char * test_number_3 = "9";
    char * test_number_4 = "12";
    char * test_number_5 = "14";
    char * test_number_6 = "2054";
    char * test_number_7 = "2004";
    char * test_number_8 = "2062";
    assert(is_divisible_by_4(test_number_1) == 1);
    assert(is_divisible_by_4(test_number_2) == 1);
    assert(is_divisible_by_4(test_number_3) == 0);
    assert(is_divisible_by_4(test_number_4) == 1);
    assert(is_divisible_by_4(test_number_5) == 0);
    assert(is_divisible_by_4(test_number_6) == 0);
    assert(is_divisible_by_4(test_number_7) == 1);
    assert(is_divisible_by_4(test_number_8) == 0);
    printf("unit_tests_is_divisible_by_4 works\n");
}

void unit_tests_is_divisible_by_3(void)
{
    char * test_number_1 = "3";
    char * test_number_2 = "6";
    char * test_number_3 = "60";
    char * test_number_4 = "100";
    char * test_number_5 = "102";
    char * test_number_6 = "222222";
    char * test_number_7 = "222223";
    assert(is_divisible_by_3(test_number_1) == 1);
    assert(is_divisible_by_3(test_number_2) == 1);
    assert(is_divisible_by_3(test_number_3) == 1);
    assert(is_divisible_by_3(test_number_4) == 0);
    assert(is_divisible_by_3(test_number_5) == 1);
    assert(is_divisible_by_3(test_number_6) == 1);
    assert(is_divisible_by_3(test_number_7) == 0);
    printf("unit_tests_is_divisible_by_3 works\n");
}

void unit_tests_count_digits(void)
{
    char * test_number_1 = "10000";
    char * test_number_2 = "1234";
    assert(strcmp(count_digits(test_number_1), "1") == 0);
    assert(strcmp(count_digits(test_number_2), "4") == 0);;
    printf("unit_tests_count_digits works\n");
}

void unit_tests_sum_digits(void)
{
    char * test_number_1 = "10000";
    char * test_number_2 = "1234";
    assert(strcmp(sum_digits(test_number_1), "1") == 0);
    assert(strcmp(sum_digits(test_number_2),"10") == 0);
    printf("unit_tests_sum_digits works\n");
}

void unit_test_get_last_digit(void)
{
    char * test_number_1 = "123456789";
    char * test_number_2 = "9876543421";
    assert(get_last_digit(test_number_1) == 9);
    assert(get_last_digit(test_number_2) == 1);
    printf("unit_test_get_last_digit works\n");
}
void unit_test_get_last_two_digits(void)
{
    char * test_number_1 = "123456789";
    char * test_number_2 = "9876543421";
    assert(get_last_two_digits(test_number_1) == 89);
    assert(get_last_two_digits(test_number_2) == 21);
    printf("unit_test_get_last_two_digits works\n");
}

void unit_tests_is_divisible_by_2(void)
{
    char * test_number_1 = "200";
    char * test_number_2 = "202";
    char * test_number_3 = "204";
    char * test_number_4 = "206";
    char * test_number_5 = "211";
    assert(is_divisible_by_2(test_number_1) == 1);
    assert(is_divisible_by_2(test_number_2) == 1);
    assert(is_divisible_by_2(test_number_3) == 1);
    assert(is_divisible_by_2(test_number_4) == 1);
    assert(is_divisible_by_2(test_number_5) == 0);
    printf("unit_tests_is_divisible_by_2 works\n");
}

void unit_tests(void)
{
    unit_test_get_last_digit();
    unit_test_get_last_two_digits();
    unit_tests_sum_digits();
    unit_tests_count_digits();
    unit_tests_is_divisible_by_2();
    unit_tests_is_divisible_by_3();
    unit_tests_is_divisible_by_4();
    unit_tests_is_divisible_by_5();
    unit_tests_is_divisible_by_6();
    unit_tests_is_divisible_by_9();
    unit_tests_is_divisible_by_10();
    unit_tests_is_divisible_by_anything_else();
    unit_tests_array_of_functions();
}

// -----------------------------------------------------------------END UNIT TEST SECTION -----------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    int c;
    static char optstring[] = "hqimputs:d:l:";

    int n = 0;
    double total_time, start_time, get_function_run_time();
    //from https://tutoria.ualg.pt/2019/pluginfile.php/132031/mod_resource/content/1/00-Revis%C3%B5es.html
    while ( (c = getopt(argc, argv, optstring)) != -1 )
      switch (c) {
         case 'h':
            printf("Command list:\n\
h -> for help\n\
q -> qsort\n\
i -> to use insertion sort\n\
m -> to use merge sort\n\
p -> enables output prints\n\
u -> runs unit tests\n\
t -> enables time tests\n\
s: -> sequential function\n\
d: -> pthread function\n\
l: -> runs functions in loop\n");
            break;
        case 'q':
            printf("Sorting the function with qSort sort\n");
            q_sort = 1;
            break;
        case 'i':
            printf("Sorting the function with insertion sort\n");
            i_sort = 1;
            if(merge_sort == 1)
                printf("Insertion sort And MergeSort option Selected, Running MergeSort only\n");
            break;
        case 'm':
            printf("Sorting the function with merge sort\n");
            merge_sort = 1;
            if(i_sort == 1)
                printf("Insertion sort And Merge Sort option Selected, Running MergeSort only\n");
            break;
        case 'p':
            printf("Found option p and prints are active\n");
            print_output = 1;
            break;
         case 'u':
            printf("Found option u and it will run unit tests\n");
            unit_tests();
            break;
        case 't':
            printf("Found option t and it count execution time of the program\n");
            time_output = 1;
            break;
        case 's':
            printf("Running Sequential with arg %s\n", optarg);
            if(strcmp(optarg, "1") == 0)
                sequential_default(argv[optind++]);
            else if(strcmp(optarg, "2") == 0)
                sequential_optimization(argv[optind++]);
            else
                printf("Not input_string valid argument, try with:\n\
1 -> for default sequential\n\
2 -> for sequential with otimization\n");
            break;
        case 'd':
            printf("Running Pthreads with arg %s\n", optarg);
            if(strcmp(optarg, "1") == 0)
                pthread_default(argv[optind++]);
            else if(strcmp(optarg, "2") == 0)
                pthread_default_with_3_threads(argv[optind++]);
            else if(strcmp(optarg, "3") == 0)
                pthread_optimzation_with_custom_number_of_threads(argv[optind++]);
            else if(strcmp(optarg, "4") == 0)
                pthread_with_mutex(argv[optind++]);
            else
                printf("Not input_string valid argument\n\
1 -> for pthread function with 2 pthreads\n\
2 -> for pthread function with 3 pthreads\n\
3 -> for pthread function with N threads\n\
4 -> for pthread function with N threads with mutexes\n");
            break;
        case 'l':
            printf("Running functions in loop 100 times with arg %s\n", optarg);
            for(int i = 0; i < 100; i++)
            {
                start_time=get_function_run_time();
                if(strcmp(optarg, "1") == 0)
                    sequential_default(argv[optind]);
                else if(strcmp(optarg, "2") == 0)
                    sequential_optimization(argv[optind]);
                else if(strcmp(optarg, "3") == 0)
                    pthread_default(argv[optind]);
                else if(strcmp(optarg, "4") == 0)
                    pthread_default_with_3_threads(argv[optind]);
                else if(strcmp(optarg, "5") == 0)
                    pthread_optimzation_with_custom_number_of_threads(argv[optind]);
                else if(strcmp(optarg, "6") == 0)
                    pthread_with_mutex(argv[optind]);
                total_time += get_function_run_time() - start_time;
            }
            printf("total run time %lf\n", total_time / 100);
        }
    return 0;
}