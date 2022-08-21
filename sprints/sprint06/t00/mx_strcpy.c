#include <stdio.h>

char *mx_strcpy(char *dst, const char *src);

char *mx_strcpy(char *dst, const char *src) {
    for (int i = 0; src[i]; i++) {
        dst[i] = src[i];
    }

    return dst;
}

int main(void) {
    char orig[] = "Hello hyi";
    char copy[130];

    mx_strcpy(copy, orig);

    printf("%s\n", copy);
}
