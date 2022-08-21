#include <stdio.h>
#include <unistd.h>

void mx_str_separate(const char *str, char delim);
void mx_printchar(char c);

void mx_str_separate(const char *str, char delim) {
    for (int i = 0; str[i]; i++) {
        if (str[i] != delim) {
            mx_printchar(str[i]);
        }
        else {
            mx_printchar('\n');
            while (str[i+1] == delim) {
                i++;
            }
        }
    }
    mx_printchar('\n');
}
