char *mx_strncpy(char *dst, const char *src, int len) {
    char *tmp = dst;
    for (int i = 0; (*dst++ = *src++) && i < len - 1; i++);
    return tmp;
}

