#include "../inc/header.h"

void mx_printint(int n) {
    int last_n = 0;
    int counter = 0;
    if (n < 0) {
        mx_printchar('-');
        n *= -1;
    }
    if (n == 0) {
        mx_printchar('0');
    }
    int new_n = n;
    while (n > 0) {
        last_n = n % 10;
        n -= last_n;
        n = n / 10;
        counter++;
    }
    n = new_n;
    int matrix_n[counter];
    int j = 0;
    while (n > 0) {
        last_n = n % 10;
        n -= last_n;
        n = n / 10;
        matrix_n[j] = last_n;
        j++;
    }
    for (int i = counter - 1; i >= 0; i--) {
        mx_printchar(matrix_n[i] + 48);
    }
}

