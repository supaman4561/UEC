#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define LINE_SIZE 256
#define NAME_LENGTH 256

typedef struct node_tag {
  struct node_tag *next;
  char name[NAME_LENGTH];
  int point;
}node_t;

node_t *new_node(char nm[NAME_LENGTH], int point, node_t *p);
int insert_by_name(char nm[NAME_LENGTH], int point, node_t *head);
int comp_by_name(char name1[NAME_LENGTH], char name2[NAME_LENGTH]);
void move_nodes_by_points(node_t *head_name, node_t *head_point);
void show_list(node_t *p);

int main(int argc, char *argv[])
{
  FILE *fp;
  char name[NAME_LENGTH], str[LINE_SIZE];
  node_t head_name, head_point;
  int point,i;
  
  if (argc < 2) {
    printf("Usage: ./No2 [filename]\n");
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Failure open the file...\n");
      return -1;
    }

    head_name.next = NULL;
    i = 0;
    while (fscanf(fp, "%d,%s", &point, name) != EOF) {
      insert_by_name(name, point, &head_name);
    }

    printf("***name order***\n");
    show_list(&head_name);

    move_nodes_by_points(&head_name, &head_point);

    printf("***points order***\n");
    show_list(&head_point);

    printf("Confirm that linear list 'head_name' is empty.\n");
    show_list(&head_name);

  }
  
  return 0;
}

node_t *new_node(char nm[NAME_LENGTH], int point, node_t *p)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));

  if (tmp == NULL) {
    printf("Failure allocate memory...\n");
    return NULL;
  } else {
    strcpy(tmp->name, nm);
    tmp->point = point;
    tmp->next = p;
    return tmp;
  }
}

int insert_by_name(char nm[NAME_LENGTH], int point, node_t *head)
{
  node_t *tmp, *p;

  tmp = new_node(nm, point, NULL);
  if (tmp == NULL) return FAILURE;
  p = head;
  while (p->next != NULL) {
    if(comp_by_name(tmp->name, p->next->name) == 1){
      break;
    } else {
      p = p->next;
    }
  }

  tmp->next = p->next;
  p->next = tmp;
  return SUCCESS;
}

/*
  1: name1 -> name2
  0: name1 = name2
 -1: name2 -> name1
*/
int comp_by_name(char name1[NAME_LENGTH], char name2[NAME_LENGTH])
{
  char c1, c2;
  int i;

  i = 0;
  while (name1[i] != '\0' && name2[i] != '\0') {
    if (name1[i] < name2[i]) {
      return 1;
    } else if (name1[i] > name2[i]) {
      return -1;
    }
    i++;
  }

  return 0;
}

/** 
 * move nodes from linear list "head_name" 
 * to another linear list "head_point" according to point.
 */
void move_nodes_by_points(node_t *head_name, node_t *head_point)
{
  node_t *target, *target_prev, *p, *head_point_rear;

  head_point_rear = head_point;
  while (head_name->next != NULL) {
    target_prev = head_name;
    p = head_name;
    while (p->next != NULL) {
      if (target_prev->next->point < p->next->point) {
        target_prev = p;
      }
      p = p->next;
    }
    target = target_prev->next;
    target_prev->next = target->next;
    head_point_rear->next = target;
    head_point_rear = head_point_rear->next;
  }
}

/**
 * show all contents of linear list.
 */
void show_list(node_t *head)
{
  node_t *p;
  p = head->next;
  while (p != NULL) {
    printf("name: %s, point: %d\n", p->name, p->point);
    p = p->next;
  }
}
