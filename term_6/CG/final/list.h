#ifndef __LIST_H_
#define __LIST_H_

typedef enum type_tag {TYPE_TEXTURE=0, TYPE_PLANE, TYPE_OBB} type_t;

typedef struct cell {
    struct cell *next;
    type_t type;
    void *data;
}cell_t;

cell_t *create_cell(type_t type, void *obj);

cell_t *append_cell(cell_t *head, type_t type, void *obj);

void free_cell(cell_t *head);

#endif 