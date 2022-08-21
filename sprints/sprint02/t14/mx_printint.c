#include <stdio.h>
#include "mx_printchar.c"

void mx_printint(int n);

void mx_printint(int n) {
    long int tmp = 0;
    while (n) {
        tmp = tmp * 10 + (n % 10);
        n /= 10;
    }
    while (tmp) {
        mx_printchar((tmp % 10) + 48);
        tmp /= 10;
    }
}
