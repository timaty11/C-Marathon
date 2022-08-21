#include <stdlib.h>
#include <stdbool.h>

bool mx_isspace(char c);
void mx_strdel(char **str);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_strncpy(char *dst, const char *src, int len);

char *mx_strtrim(const char *str);

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int first_letter = 0;
    int last_letter = 0;
    for (int i = 0; str[i]; i++) {
        if (!mx_isspace(str[i])) {
            first_letter = i;
            break;
        }
    }
    for (int i = mx_strlen(str) - 1; i > 0; i--) {
        if (!mx_isspace(str[i]) && str[i] != 0) {
            last_letter = i;
            break;
        }
    }
    char *spaceless = mx_strnew(last_letter - first_letter + 2);
    spaceless = mx_strncpy(spaceless, &str[first_letter], (last_letter - first_letter + 1));
    return spaceless;
}

