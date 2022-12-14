#include <stdio.h>

char*mx_strjoin(char const *s1, char const *s2);
char *mx_strcat(char *s1, const char *s2);
int mx_strlen(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strdup(const char *str);
char *mx_strnew(const int size);

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL || s2 == NULL) {
        if (s1 == NULL && s2 == NULL)
            return NULL;
        else if (s1 == NULL)
        {
            return mx_strdup(s2);
        }
        else
            return mx_strdup(s1);
    }
    int size = mx_strlen(s1) + mx_strlen(s2) - 2;
    char *conc = mx_strnew(size);
    mx_strncpy(conc, s1, mx_strlen(s1) - 1);
    mx_strcat(conc, s2);
    return conc;
}

