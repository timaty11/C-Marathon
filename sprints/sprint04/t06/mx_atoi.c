int mx_atoi(const char *str);
bool mx_isdigit(int c);
bool mx_isspace(char c);

int mx_atoi(const char *str) {
    int neg = 0;
    int tmp = 0;
    if (str[0] == '-') {
        neg = 1;
    }

	for (int i = 0; str[i]; i++) {
	    if (!mx_isdigit(str[i])) {
            if (str[0] == '-') {
                i++;
            }
        }
        else if (mx_isspace(str[i])) {
            break;
        }
        else {
            tmp *= 10;
            tmp += str[i];
            tmp -= '0';
        }
	}
    if (neg) {
        return (-1 * tmp);
    }
    else {
        return tmp;
    }
}

