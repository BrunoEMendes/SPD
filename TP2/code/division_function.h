#ifndef DIVISION_FUNCTION_H
#define DIVISION_FUNCTION_H

long get_last_digit(char * s);
char *str_dup(const char *s);
long get_last_digit(char * s);
long get_last_two_digits(char * s);
char * sum_digits(char * s);
char * count_digits(char * s);
long is_divisible_by_2(char * s);
long is_divisible_by_3(char * s);
long is_divisible_by_4(char *s);
long is_divisible_by_5(char * s);
long is_divisible_by_6(char * s);
long is_divisible_by_9(char * s);
long is_divisible_by_10(char * s);
long is_divisible_by_10_2_5(long two, long five);
long is_divisible_by_anything_else(char *s, long n);
long is_divisible_by_anything_else_number(long number, long n);
#endif