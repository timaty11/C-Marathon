#include "hex_to_nbr.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) {
        return 0;
    }
    int i = 0;
    for ( ; hex[i] != '\0'; i++);

    unsigned long res = 0;
    unsigned long dec = 1;

    for (int j = i - 1; j >= 0; j--) {
        if (mx_isdigit(hex[j])) {
            res += ((hex[j] - 48) * dec);
            dec *= 16;
        }
        else if(mx_isalpha(hex[j])) {
            if(mx_isupper(hex[j])) {
                res += ((hex[j] - 55) * dec);
                dec *= 16;
            }
            else {
                res += ((hex[j] - 87) * dec);
                dec *= 16;
            }
        }
    }
    return res;
}

