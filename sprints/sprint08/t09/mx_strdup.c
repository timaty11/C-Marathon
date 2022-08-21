#include "only_smith.h"

char *mx_strdup(const char *str) {
    int size = mx_strlen(str) - 1;
    char *copy = mx_strnew(size);
    mx_strncpy(copy, str, size);
    return copy;
}

