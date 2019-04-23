#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1    
#define FAILURE 0    

typedef struct node_tag {
  struct node_tag *next;
  char* name;      
  int point;       
} node_t;                 

node_t *new_node(char *nm, int pnt, node_t *p);
int insert_nameorder(char *nm, int pnt, node_t **pp);
int move_nodes_pointorder(node_t *p_nmodr, node_t **pp_ptodr);
void show_list(node_t *p);
void free_list(node_t *p);

int main(int argc, char **argv)
{
  FILE *fp;
  node_t *head_nmodr, *head_ptodr;
  char *name;
  int point;

  if (argc < 2) {
    printf("Usage: ./No2 [filename]\n");
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Failed to open the file...\n");
      return -1;
    }

    /* initialize */
    head_nmodr = NULL;
    head_ptodr = NULL;

    while(fscanf(fp, "%d,%s", &point, name) != EOF) {
      insert_nameorder(name, point, &head_nmodr);
    }

    printf("***name order***\n");
    show_list(head_nmodr);

    move_nodes_pointorder(head_nmodr, &head_ptodr);

    printf("***point order***\n");
    show_list(head_ptodr);
    
    fclose(fp);
    free_list(head_nmodr);
    free_list(head_ptodr);
  }

  return 0;
}

/**
 * allocate memory and return new node.
 */
node_t *new_node(char *nm, int pnt, node_t *p)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));
  
  if (tmp == NULL) {
    printf("Failed to allocate memory...\n");
    return NULL;
  }

  tmp->name = (char *)malloc(sizeof(char) * strlen(nm));

  if (tmp->name == NULL) {
    printf("Failed to allocate memory...\n");
    return NULL;
  } else {
    strcpy(tmp->name, nm);
    tmp->point = pnt;
    tmp->next = p;
    return tmp;
  }
}

/**
 * insert a node to the linear list in order of name.
 */
int insert_nameorder(char *nm, int pnt, node_t **pp)
{
  node_t *tmp;
  tmp = new_node(nm, pnt, NULL);

  if (tmp == NULL) {
    return FAILURE;
  }

  if (*pp == NULL)  {
    *pp = tmp;
  } else {
    while((*pp) != NULL && (strcmp(tmp->name, (*pp)->name)) > 0 ) {
      pp = &((*pp)->next);
    }
    tmp->next = *pp;
    *pp = tmp;
  }

  return SUCCESS;
}

/**
 * move nodes from a linear list which is sorted by name 
 * to another linear list in order of point.
 */
int move_nodes_pointorder(node_t *p_nmodr, node_t **pp_ptodr)
{
  node_t *tmp;
  while (p_nmodr != NULL) {

    tmp = new_node(p_nmodr->name, p_nmodr->point, NULL);
    if (tmp == NULL) {
      return FAILURE;
    }

    if (*pp_ptodr == NULL) {
      *pp_ptodr = tmp;
    } else {
      while ((*pp_ptodr) != NULL && ( tmp->point < (*pp_ptodr)->point )) {
        pp_ptodr = &((*pp_ptodr)->next);
      }
      tmp->next = *pp_ptodr;
      *pp_ptodr = tmp;
    }

    p_nmodr = p_nmodr->next;
  }

  return SUCCESS;
}

/**
 * show all nodes in linear list.
 */
void show_list(node_t *p)
{
  while(p != NULL)
  {
    printf("name:%s,Point:%d\n", p->name, p->point);
    p = p->next;
  }
}

/**
 * free memory of the list.
 */
void free_list(node_t *p)
{
  node_t *q;

  while (p != NULL) {
    q = p;
    p = p->next;
    free(q);
  }
}