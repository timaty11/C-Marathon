#include "../inc/header.h"

double mx_pow(double n, int pow) {
    if (pow == 0) {
        return 1;
    }
    float result = n;
    for (int i = 0; i < pow - 1; i++) {
        result = (float)(result *n);
    }
    return result;
}

