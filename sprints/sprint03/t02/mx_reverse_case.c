#include <stdio.h>
#include <stdbool.h>

bool mx_islower(int c);
bool mx_isupper(int c);
int mx_tolower(int c);
int mx_toupper(int c);

void mx_reverse_case(char *s);

void mx_reverse_case(char *s) {
    char tmp[100];

    for (int i = 0; s[i]; i++) {
        if (mx_islower(s[i])) {
            tmp[i] = s[i];
            tmp[i] = mx_toupper(tmp[i]);
        }
        else if (mx_isupper(s[i])) {
            tmp[i] = s[i];
            tmp[i] = mx_tolower(tmp[i]);
        }
        else {
            tmp[i] = s[i];
        }
    }
    s = tmp;
}
