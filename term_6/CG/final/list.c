#include <stdio.h>
#include <stdlib.h>
#include "list.h"

cell_t *create_cell(type_t type, void *obj) 
{
    cell_t *p;
    p = (cell_t *)malloc(sizeof(cell_t));
    if (p == NULL) {
        printf("Could not allocate memory.");
    }
    p->type = type;
    p->data = obj;
    p->next = NULL;

    return p;
}

cell_t *append_cell(cell_t *head, type_t type, void *obj) 
{
    cell_t *p;
    p = create_cell(type, obj);

    if (head == NULL) {
        return p;
    }
    p->next = head->next;
    head->next = p;
    return head;
}

void free_cell(cell_t *head)
{
    if (head != NULL) {
        if (head->next != NULL) {
            free_cell(head->next);
        }
        free(head->data);
        free(head);
    }
}