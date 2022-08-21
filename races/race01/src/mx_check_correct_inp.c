#include "../inc/header.h"

int mx_check_correct_inp(char *str, int len) {
    for (int i = 0; i < len; i++) {
        if(i == 0 && str[i] == '-') {
            continue;
        }
        if (mx_isdigit(str[i]) || str[i] == '?') {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

