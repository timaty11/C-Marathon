void mx_printchar(char c);
void mx_pyramid(int n);

void mx_pyramid(int n) {
    int i;
    int j= 0;
    int r = 0;
    int lastSlashSpaces = 0;
    int a = 0;

    if (n < 2)
    {
        return;
    }
    else
    {
        int k = n - 1;
        for (i = 0; i < k; i++)
        {
            char splitter[] = " ";
            // if (i == k - 1)
            //     splitter[0] = '_';
            for (r = 0; r < k - i; r++)//для отступов в начале строки
            {
                mx_printchar(' ');
            }
            for (j = 0; j <= i; j++)
            {
                if (j == 0)
                    mx_printchar('/');
                else {
                    for(int i = 0; splitter[i]; i++) {
                        mx_printchar(splitter[i]);
                    }
                }
            }
            if (i == 0)
            {
                mx_printchar('\\'); // верхуйшка ебнутая
                mx_printchar('\n');
                continue;
            }
            for (a = 0; a <= j - 1; a++)
            {
                if (a == i - 1)
                {
                    mx_printchar('\\'); //центральная правая
                }
                else
                {
                    for(int i = 0; splitter[i]; i++) {
                        mx_printchar(splitter[i]);
                    }

                }

            }
            if (i - 1 < k / 2)
            {
                lastSlashSpaces = 0;

                for (int e = 0; e < i - 1; e++)
                {
                    lastSlashSpaces++;
                    if (i != 0)
                        mx_printchar(' ');
                }
                mx_printchar('\\'); // крайняя самая правая сторона
            }
            else
            {
                for (int f = 0; f < lastSlashSpaces; f++)
                {
                    for(int i = 0; splitter[i]; i++) {
                        mx_printchar(splitter[i]);
                    }
                }
                mx_printchar('|');
                lastSlashSpaces--;
            }
            mx_printchar('\n');
        }
        mx_printchar('/');
        for (i = 0; i < 2 * k - 1; i++) {
            mx_printchar('_');
        }
        mx_printchar('\\');
        mx_printchar('|');
        mx_printchar('\n');
        return;
    }
}

