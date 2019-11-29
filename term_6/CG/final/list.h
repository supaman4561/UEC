#ifndef __LIST_H_
#define __LIST_H_

typedef struct cell {
    struct cell *next;
    void *data;
}cell_t;

cell_t *create_cell(void *obj);

cell_t *append_cell(cell_t *head, void *obj);

#endif 