#include <stdlib.h>

int *mx_copy_int_arr(const int *src, int size);

int *mx_copy_int_arr(const int *src, int size) {
    if (src == NULL || size < 1) {
        return NULL;
    }
    int *copy = malloc(size);
    for (int i = 0; i < size; i++) {
        if (&src[i] == NULL) {
            return NULL;
        }
        copy[i] = src[i];
    }
    return copy;
}

