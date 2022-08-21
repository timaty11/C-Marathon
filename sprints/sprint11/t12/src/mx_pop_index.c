#include "../inc/list.h"

void mx_pop_index(t_list **list, int index) {
    t_list *head = *list, *p;
    int counter = 0;
    if (index == 0) {
        mx_pop_front(&head);
    }
    while (head->next != NULL) {
        if (counter == index) {
            p = head->next;
            mx_pop_back(&head);
            head->next = p;
        }
        counter++;
        head = head->next;
    }
    if (counter < index) {
        mx_pop_back(&head);
    }
}

