#include <stdio.h>
#include <stdbool.h>

double mx_pow(double n, unsigned int pow);
bool mx_is_narcissistic(int num);

bool mx_is_narcissistic(int num) {
    if (num < 0) {
        return false;
    }

    int tmp = num;
    int num_to_get = 0;
    int size = 0;

    while (tmp) {
        tmp /= 10;
        size++;
    }

    tmp = num;
    while (tmp) {
        num_to_get += (mx_pow((tmp % 10), size));
        tmp /= 10;
    }

    if (num_to_get == num) {
        return true;
    }
    else {
        return false;
    }
}
