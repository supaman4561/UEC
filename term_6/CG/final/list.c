#include <stdio.h>
#include <stdlib.h>
#include "list.h"

cell_t *create_cell(void *obj) 
{
    cell_t *p;
    p = (cell_t *)malloc(sizeof(cell_t));
    if (p == NULL) {
        printf("Could not allocate memory.");
    }
    p->data = obj;
    p->next = NULL;

    return p;
}

cell_t *append_cell(cell_t *head, void *obj) 
{
    cell_t *p;
    p = create_cell(obj);

    if (head == NULL) {
        return p;
    }
    p->next = head->next;
    head->next = p;
    return head;
}