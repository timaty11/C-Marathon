#pragma once

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_list {
    void *data;
    struct s_list *next;
}              t_list;

int mx_list_size(t_list *list);

#endif
