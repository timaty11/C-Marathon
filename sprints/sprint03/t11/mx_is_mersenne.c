#include <stdio.h>
#include <stdbool.h>

double mx_pow(double n, unsigned int pow);
bool mx_is_prime(int num);
bool mx_is_mersenne(int n);

bool mx_is_mersenne(int n) {
    int temp = 0;
    for (int i = 1; temp < n; i++) {
        if (mx_is_prime(i)){
            temp = mx_pow(2, i) - 1;
            if (n == temp) {
               return true;
            }
        }
    }
    return false;
}
