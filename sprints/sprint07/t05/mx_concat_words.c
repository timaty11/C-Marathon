#include <stdlib.h>

char *mx_strcat(char *s1, const char *s2);
int mx_strlen(const char *s);
char *mx_strncpy(char *dst, const char *src, int len);
void mx_strdel(char **str);
char *mx_strdup(const char *str);
char*mx_strjoin(char const *s1, char const *s2);
char *mx_strnew(const int size);

char *mx_concat_words(char **words);

char *mx_concat_words(char **words) {
    if (words == NULL) {
        return 0;
    }
    char *stnc = mx_strjoin(words[0], " ");
    mx_strdel(words[0]);
    for (int i = 1; words[i]; i++) {
        stnc = mx_strjoin(stnc, words[i]);
        if (words[i + 1] != NULL) {
            stnc = mx_strjoin(stnc, " ");
        }
        mx_strdel(&words[i]);
    }
    stnc = mx_strjoin(stnc, "\0");
    return stnc;
}

