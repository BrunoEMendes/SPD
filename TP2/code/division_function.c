#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>

// função do professor Pedro Guerreiro de PI 2019/2020
//https://tutoria.ualg.pt/2019/pluginfile.php/116217/mod_resource/content/12/our_strings.c
char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

// gets last char of input_string fstring and converts it to long
long get_last_digit(char * s)
{
    return s[strlen(s) - 1] - '0';
}

// gets penultimate digit
long get_last_two_digits(char * s)
{
    assert(strlen(s) > 1);
    return (s[strlen(s) - 2] - '0') * 10 + get_last_digit(s);
}

// sums the digits
char * sum_digits(char * s)
{
    char * res = malloc(strlen(s) * sizeof(char));
    long sum = 0;
    for(long i = 0; i < strlen(s); ++i)
        if(s[i] >= '0' && s[i] <= '9')
            sum += (s[i] - '0');
    sprintf(res, "%ld", sum);
    return res;
}


// counts the total of digits
char * count_digits(char * s)
{
    char * res = malloc(12);
    long sum = 0;
    for(long i = 0; i < strlen(s); ++i)
        if(s[i] > '0' && s[i] <= '9')
            sum ++;
    sprintf(res, "%ld", sum);
    return res;
}

// checks if its divisible by_2
long is_divisible_by_2(char * s)
{
    return get_last_digit(s) % 2 == 0;
}

// check if its divisible by 3
long is_divisible_by_3(char * s)
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
    long n = atoi(sum);
    long res = n == 3 || n == 6 || n == 9;
    free(sum);
    free(count);
    return res;
}

// check if its divisible by 4
// TODO
// gotta find better solution
long is_divisible_by_4(char *s)
{
    long n = get_last_digit(s);
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
long is_divisible_by_5(char * s)
{
    long n = get_last_digit(s);
    return n == 5 || n == 0;
}

// check if its divisible by 6
long is_divisible_by_6(char * s)
{
    return is_divisible_by_2(s) && is_divisible_by_3(s);
}

long is_divisible_by_9(char * s)
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
    long n = atoi(sum);
    long res = n == 9;
    free(sum);
    free(count);
    return res;
}

// ------------------------------ FUNÇÕES FACTORIAIS -----------------------------------------
// check if its divisible by 10
long is_divisible_by_10(char * s)
{
    return get_last_digit(s) == 0;
}

//if two and 5 are divisible
long is_divisible_by_10_2_5(long two, long five)
{
    return two && five;
}

long is_divisible_by_anything_else(char *s, long n)
{
    return atoi(s) % n == 0;
}

long is_divisible_by_anything_else_number(long number, long n)
{
    return number % n == 0;
}