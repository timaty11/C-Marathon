#include "list.h"

t_list *mx_create_node(void *data) {
    t_list *tmp = (t_list*)malloc(sizeof(t_list));
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

