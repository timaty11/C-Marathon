void mx_printchar(char c);
int mx_strlen(const char *s);

void mx_printstr(const char *str) {
    for (int i = 0; i < mx_strlen(str); i++) {
        mx_printchar(str[i]);
    }
}
