#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESS 1
#define FAILURE 0
#define LINESIZE 256

typedef double data_t;
typedef struct node_tag {
  data_t data;
  struct node_tag *next;
} node_t;

node_t *new_node(data_t data, node_t *p);
int insert_rear(data_t x, node_t **pp);
double sum(node_t *p);
double sort_sum(node_t *head);
void free_list(node_t *head);

/* for debug */
void show_list(node_t *p);


int main(int argc, char *argv[])
{
  FILE *fp;
  char str[LINESIZE];
  node_t *head;
  double tmp, s, s_sorted;
  int i;

  if (argc < 2) {
    printf("Usage: ./No1_A [filename]\n");
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Failure open the file...\n");
      return -1;
    }

    head = NULL;
    i = 0;
    while (fscanf(fp, "%lf", &tmp) != EOF) {
      insert_rear(tmp, &head);
    }
    
    s = sum(head);
    
    printf("sum: %lf\n", s);
    
    s = sort_sum(head);
    
    printf("sum(sorted): %lf\n", s);
    
    free_list(head);
    fclose(fp);
  }
  
  return 0;
}

node_t *new_node(data_t x, node_t *p)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));

  if (tmp == NULL) {
    printf("Failure allocate memory...\n");
    return NULL;
  } else {
    tmp->data = x;
    tmp->next = p;
    return tmp;
  }
}

int insert_rear(data_t x, node_t **pp)
{
  node_t *tmp;

  tmp = new_node(x, NULL);
  if (tmp == NULL) return FAILURE;
  while (*pp != NULL) {
    pp = &((*pp)->next);
  }
  *pp = tmp;

  return SUCCESS;
}

double sum(node_t *p)
{
  double s;

  s = 0;

  while(p != NULL) {
    s += p->data;
    p = p->next;
  }
  
  return s;
}

double sort_sum(node_t *head)
{
  double s, tmp;
  
  node_t *p1, *p2;

  p2 = head;
  while(p2->next != NULL) {
    p2 = p2->next;
  }

  while(p2 != head) {
    p1 = head;
    while(p1->next != p2) {
      if (fabs(p1->data) > fabs(p2->data)) {
	tmp = p1->data;
	p1->data = p2->data;
	p2->data = tmp;
      }
      p1 = p1->next;
    }
    p2 = p1;
  }

  // for debug
  // show_list(head);
  s = sum(head);
  
  return s;
}

void free_list(node_t *head)
{
  node_t *t1, *t2;

  while(head->next == NULL) {
    t1 = head;
    while(t1->next != NULL) {
      t1 = t1->next;
    }
    free(t1->next);
  }
}

/* for debug */
void show_list(node_t *p)
{
  while (p != NULL) {
    printf("%lf\n", p->data); 
    p = p->next;
  }
}
