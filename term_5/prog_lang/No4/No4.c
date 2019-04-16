#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef int data_t;
typedef int frequency_t;
typedef struct node_tag {
  data_t data;
  frequency_t frequency;
  struct node_tag *left;
  struct node_tag *right;
}node_t;

node_t *new_node(data_t x);
int insert(data_t x, node_t **pp);
node_t *is_member(data_t x, node_t *p);
void show_preorder(node_t *p);

int main(int argc, char *argv[])
{
  FILE *fp;
  node_t *root, *tmp;
  data_t num;

  if (argc < 2) {
    printf("Usage: ./No4 [filename]");
    return -1;
  } else {

    if ((fp = fopen(argv[1], "r")) == NULL) {
      printf("Failed to open the file.\n");
      return -1;
    }

    /* initialize */
    root = NULL;
    
    while(fscanf(fp, "%d", &num) != EOF) {
      if ((tmp = is_member(num, root)) == NULL) {
	if (insert(num, &root) == FAILURE) {
	  printf("Failed to insert new node.\n");
	}
      } else {
	tmp->frequency += 1;
      }
    }

    printf("data: frequensy\n");
    show_preorder(root);
  }
  
  return 0;
}

node_t *new_node(data_t x)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));

  if (tmp == NULL) {
    printf("ERROR: Failure allocate memory\n");
  } else {
    tmp->data = x;
    tmp->frequency = 1;
    tmp->left = NULL;
    tmp->right = NULL;
  }

  return tmp;
}

int insert(data_t x, node_t **pp)
{
  node_t *tmp;

  if (*pp == NULL) {
    tmp = new_node(x);
    if (tmp == NULL) {
      return FAILURE;
    }
    *pp = tmp;
    return SUCCESS;
  } else {
    if (x < (*pp)->data) {
      insert(x, &((*pp)->left));
    } else {
      insert(x, &((*pp)->right));
    }
  }
}


node_t *is_member(data_t x, node_t *p)
{
  if (p == NULL) {
    return NULL;
  } else {
    if (x == p->data) {
      return p;
    } else if (x < p->data) {
      return is_member(x, p->left);
    } else {
      return is_member(x, p->right);
    }
  }
}

void show_preorder(node_t *p)
{
  if (p != NULL) {
    printf("%4d: %9d\n", p->data, p->frequency);
    show_preorder(p->left);
    show_preorder(p->right);
  }
}
