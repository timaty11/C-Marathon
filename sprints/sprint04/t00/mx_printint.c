void mx_printchar(char c);
void mx_printint(int n);

void mx_printint(int n) {
    int tmp[20];
    int counter = 0;
    while (n) {
        tmp[counter] = n % 10;
        n /= 10;
        counter++;
    }
    for (int i = counter - 1; i >= 0; i--) {
        mx_printchar(tmp[i] + 48);
    }
}

