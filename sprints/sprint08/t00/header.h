#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

typedef struct s_student {
    char *first_name;
    char *last_name;
    int age;
}              t_student;

void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char *str);
char *mx_strcpy(char *dst, char *str);
int mx_strlen(const char *s);
int mx_strcmp(const char *s1, const char *s2);
bool mx_isdigit(char c);
bool mx_isspace(char c);
int mx_atoi(const char *str);

#endif

