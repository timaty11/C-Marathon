#include <stdio.h>
#include <unistd.h>

void mx_printstr(const char *s);

void mx_printstr(const char *s){
	write(1, s, mx_strlen(s));
	write(1, "\n", 1);
}

