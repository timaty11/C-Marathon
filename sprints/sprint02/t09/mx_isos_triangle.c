#include <stdio.h>
#include "mx_printchar.c"

void mx_isos_triangle(unsigned int length, char c) {
    for(int i = 0; i < length; i++) {
        for (int j = 0; j <= i; j++) {
            mx_printchar(c);
        }
        mx_printchar('\n');
    }
}
