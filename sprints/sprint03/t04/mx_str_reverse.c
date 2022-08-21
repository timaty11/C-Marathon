#include <stdio.h>

int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);

void mx_str_reverse(char *s) {
    int j = mx_strlen(s) - 2;
    for (int i = 0; i < mx_strlen(s)/2; i++) {
        mx_swap_char(&s[i], &s[j]);
        j--;
    }
}
