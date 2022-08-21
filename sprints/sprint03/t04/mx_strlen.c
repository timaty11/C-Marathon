#include <stdio.h>

int mx_strlen(const char *s);

int mx_strlen(const char *s){
	int counter = 0;
	do {
		counter++;
	} while (*s++);
	return counter;
}
