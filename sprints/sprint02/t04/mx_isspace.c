#include <stdio.h>
#include <stdbool.h>

bool mx_isspace(char c);

bool mx_isspace(char c) {
    if (с == 32 || c == 9 || c == 10 || c == 11 || c == 12 || c == 13) {
        return 1;
    }
    else {
        return 0;
    }
}
