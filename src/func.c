#include "func.h"
#include <math.h>

int get_divisors_number(int number) 
{
    int divisors_number = 0;
    int sqrt_int = ((int) sqrt(number)) + 1;
    for (int i = 2; i < sqrt_int; i++) 
    {
        if (number % i == 0)
        {
            divisors_number += 2;
            if (number == i * i) divisors_number--;
        }
    }
    return divisors_number;
}

int get_number_length(int number) 
{
    int len = 0;
    while (number > 0) 
    {
        len++;
        number /= 10;
    }
    return len;
}

int max(int a, int b) 
{
    return a > b ? a : b;
}