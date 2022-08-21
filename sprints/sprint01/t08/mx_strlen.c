#include <stdio.h>

int mx_strlen(const char *s);

int mx_strlen(const char *s){
	int counter = 0;
	char i = s[0];
	while (i){
		i = s[counter + 1];
		counter++;
	}
	return counter;
}
