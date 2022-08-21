#include <stdlib.h>

void mx_strdel(char**);
char *mx_strncpy(char*, const char*, int);
char *mx_strnew(const int);
int mx_count_words(const char*, char);
char **mx_strsplit(char const *s, char c) {
	int count_words = mx_count_words(s, c);
	int j = 0;
	char **result = (char**)malloc(8 * count_words);
	for (int i = 0; i < count_words; i++) {
		int length = 0;
		int start = 0;
		for (; s[j]; j++) {
			if (s[j] != c) {
				length += 1;
				if (start == 0)
					start = j;
			}
			else if (s[j] == c && length)
				break;
		}
		char* tmp = mx_strnew(length);
		for (int k = 0, m = start; m < j; k++, m++)
			tmp[k] = s[m];
		result[i] = tmp;
	}
	result[count_words] = NULL;
	return result;
}

