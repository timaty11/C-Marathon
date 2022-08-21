#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int mx_atoi(const char *str);
bool mx_isdigit(int c);
bool mx_isspace(char c);
void mx_printchar(char c);
void mx_printerr(const char *s);
int mx_strlen(const char *s);
void mx_printint(int n);
void mx_printstr(const char *str);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
int mx_strlen(const char *s);
char *mx_strtrim(const char *str);
char *mx_strdup(const char *str);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strnew(const int size);
int mx_count_qmarks(const char * str);
double mx_pow(double n, int pow);
int mx_check_correct_inp(char *str, int len);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);


#endif
