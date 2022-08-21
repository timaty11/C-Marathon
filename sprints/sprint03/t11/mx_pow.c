#include <stdio.h>

double mx_pow(double n, unsigned int pow);

double mx_pow(double n, unsigned int pow) {
    float result = n;
    for (int i = 0; i < pow - 1; i++) {
        result = (float)(result *n);
    }
    return result;
}
