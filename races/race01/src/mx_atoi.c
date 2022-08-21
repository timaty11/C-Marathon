#include "../inc/header.h"

int mx_atoi(const char *str) {
    int n = 1;
    int res = 0;
    int j = 0; 
    while(str[j]) {
        if (mx_isspace(str[j])) {
            j++;
        }
        else {
            break;
        }
    }
    if (str[j] == '-' ) {
        n = -1;
        j++;
    }
    if (str[j] == '+' ) {
        j++;
    }
    while (str[j]) {
        if (!mx_isdigit(str[j]))
            return 0;
        res = res * 10;
        res = res + (str[j] - 48);   
        j++;  
    }
    return (n * res);
}

