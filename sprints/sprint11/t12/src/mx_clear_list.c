#include "../inc/list.h"

void mx_clear_list(t_list **list) {
    if (list && *list) {
        while (*list) {
            t_list *tmp = NULL;
            if (list == NULL || *list == NULL) {
                return;
            }
            if ((*list)->next == NULL) {
                free(*list);
                *list = NULL;
            }
            else {
                tmp = (*list)->next;
                free(*list);
                *list = tmp;
            }
        }
    }
}

