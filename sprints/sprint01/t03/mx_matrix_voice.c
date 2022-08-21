#include <stdio.h>
#include <unistd.h>
#include <string.h>

void mx_matrix_voice(void){
	write(1, "\a", strlen("\a"));
}
