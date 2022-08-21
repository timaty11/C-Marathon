char *mx_strncpy(char *dst, const char *src, int len) {
    while (len--) {
        *dst = *src;
        dst++;
        src++;
    }
    return dst;
}

