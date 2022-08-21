int mx_count_qmarks(const char * str) {
    int counter = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '?') {
            counter++;
        }
    }

    return counter;
}

 