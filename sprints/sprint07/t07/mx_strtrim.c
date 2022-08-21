#include <stdbool.h>
#include <stdlib.h>

bool mx_isspace(char c);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strlen(const char *s);
char *mx_strnew(const int size);

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    int start = 0;
    for ( ; mx_isspace(str[start]); start++);
    int end = mx_strlen(str) - 1;
    for ( ; mx_isspace(str[end]); end--);
    if (end < 0) {
        end = start;
    }
    int len = end - start + 1;
    char *tmp = mx_strnew(len);

    if (tmp == NULL) {
        return NULL;
    }
    tmp = mx_strncpy(tmp, &str[start], len);
    return tmp;
}

