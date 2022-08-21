#include <stdbool.h>
#include <stdlib.h>

bool mx_isspace(char c);
void mx_strdel(char **str);
int mx_strlen(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    int j = 0;
    char *tmp1 = mx_strtrim(str);
    char *tmp2 = mx_strnew(mx_strlen(tmp1));
    if (tmp2 == NULL) {
        return NULL;
    }
    for (int i = 0; tmp1[i] != '\0'; i++) {
        if (mx_isspace(tmp1[i]))
            for (tmp2[j++] = ' '; mx_isspace(tmp1[i]); i++);
        tmp2[j++] = tmp1[i];
    }
    char *res = mx_strnew(mx_strlen(tmp2));
    if (res == NULL) {
        return NULL;
    }
    mx_strncpy(res, tmp2, mx_strlen(res) + mx_strlen(tmp2) - 3);
    mx_strdel(&tmp1);
    mx_strdel(&tmp2);
    return res;
}

