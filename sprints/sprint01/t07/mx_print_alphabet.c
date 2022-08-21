#include <stdio.h>
#include <unistd.h>

void mx_print_alphabet(void);

void mx_print_alphabet(void){
	for(int i = 0; i < 26; i++){
		if (i % 2 == 0){
			mx_printchar(i+65);
		}
		else{
			mx_printchar(i+97);
		}
	}
	mx_printchar('\n');
}
