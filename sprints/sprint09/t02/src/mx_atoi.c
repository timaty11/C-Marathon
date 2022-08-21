#include <stdbool.h>

bool mx_isdigit(int c);
bool mx_isspace(char c);

int mx_atoi(const char *str) {
    if (*str == '\0')
        return 0;

    int res = 0;
    int neg = 1;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            neg = -1;
        } else if (!mx_isdigit(str[i])) {
            if (mx_isspace(str[i]))
                continue;
            else
                return 0;
        }
        else {
            res = res * 10 + str[i] - '0';
        }
    }
    return neg * res;
}

