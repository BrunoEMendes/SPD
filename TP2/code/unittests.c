#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "f_function.h"
#include "unittests.h"


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