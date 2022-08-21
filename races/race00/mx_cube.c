void mx_printchar(char c);
void mx_cube(int n);

void mx_cube(int n) {
    if (n <= 1) {
        return;
    }
    int line; // Будет следить, на какой линии печати мы щас находимся

    for (line = 0; line < ((n + 2) + n/2 + 1); line++) {
        // ОТСТУП ПЕРЕД ПЕРВОЙ ЛИНИЕЙ (РАВЕН КОЛИЧЕСТВУ (n/2) + 1) ////
        for (int i = 0; i < ((n/2) + 1) - line; i++) {
            mx_printchar(' ');
        }

        //// HORIZONTAL LINE ////
        if (line == 0 || line == ((n + 2) + n/2) || line == (n/2 + 1)) {
            mx_printchar('+');
            for (int i = 0; i < (2 * n); i++) {
                mx_printchar('-');
            }
            mx_printchar('+');

            //// Background vertical line
            if (line == (n/2 + 1)) {
                for (int i = 0; i < (line - 1); i++) {
                    mx_printchar(' ');
                }
                mx_printchar('|');
            }
        } //// Diagonal
        else if (line > 0 && line < (n/2 + 1)) {
            mx_printchar('/');
            for (int i = 0; i < (2 * n); i++) {
                mx_printchar(' ');
            }
            mx_printchar('/');

            //// Background vertical line
            for (int i = 0; i < (line - 1); i++) {
                mx_printchar(' ');
            }
            mx_printchar('|');
        }
        else { //// Vertical line
            mx_printchar('|');
            for (int i = 0; i < (2 * n); i++) {
                mx_printchar(' ');
            }
            mx_printchar('|');

            //// Background vertical line
            if (line > (line - n/2) && line <= n) {
                if (n % 2 == 0) {
                    for (int i = 0; i <= ((n - n/2) - 1); i++) {
                        mx_printchar(' ');
                    }
                    mx_printchar('|');
                }
                else {
                    for (int i = 0; i <= ((n - n/2) - 2); i++) {
                        mx_printchar(' ');
                    }
                    mx_printchar('|');
                }
            }

            if (line == n + 1) {
                if (n % 2 == 0) {
                    for (int i = 0; i <= (n - n/2 - 1); i++) {
                        mx_printchar(' ');
                    }
                    mx_printchar('+');
                }
                else {
                    for (int i = 0; i <= (n - n/2 - 2); i++) {
                        mx_printchar(' ');
                    }
                    mx_printchar('+');
                }

            }

            if (line > n + 1 && line < ((n + 2) + n/2)) {
                for (int i = 0; i <= (n + n/2 - line); i++) {
                    mx_printchar(' ');
                }
                mx_printchar('/');
            }
        }

        mx_printchar('\n');
    }
}

