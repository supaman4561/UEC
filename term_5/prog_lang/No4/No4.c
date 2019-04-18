#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef int data_t;
typedef int frequency_t;
typedef enum {QUIT, INSERT, DELETE, SHOW} command_t;
typedef struct node_tag {
  data_t data;
  frequency_t frequency;
  struct node_tag *parent;
  struct node_tag *left;
  struct node_tag *right;
}node_t;

node_t *new_node(data_t x, node_t *p);
int insert(data_t x, node_t **pp);
int delete(data_t x, node_t **pp);
node_t *is_member(data_t x, node_t *p);
node_t *delete_min(node_t **p);
void show_inorder(node_t *p);

int main()
{
  node_t *root, *tmp;
  data_t num;
  int cmd;

  /* initialize */
  root = NULL;
  
  printf("===commands===\n");
  printf("%d: QUIT\n", QUIT);
  printf("%d: INSERT\n", INSERT);
  printf("%d: DELETE\n", DELETE);
  printf("%d: SHOW\n", SHOW);

  cmd = QUIT;
  do {
    printf("cmd>");
    scanf("%d", &cmd);
    if (cmd == QUIT) {
      
      printf("Bye!\n");

    } else if (cmd == INSERT) {
      printf("data>");
      scanf("%d", &num);
      if ((tmp = is_member(num, root)) == NULL) {
        if (insert(num, &root) == FAILURE) {
          printf("Failed to insert a new node.\n");
        } 
      } else {
        tmp->frequency += 1;
      }

    } else if (cmd == DELETE) {
      printf("data>");
      scanf("%d", &num);
      if ((tmp = is_member(num, root)) == NULL) {
        printf("The node that has the number is not exist.\n");
      } else {
        if (delete(num, &root) == FAILURE) {
          printf("Failed to delete a node.\n");
        }
      }
    } else if (cmd == SHOW) {
      printf("data: frequency\n");
      show_inorder(root);
    } else {
      printf("The command is not exist.\n");
    }
  
  }while (cmd != QUIT);
  
  return 0;
}

node_t *new_node(data_t x, node_t *p)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));

  if (tmp == NULL) {
    printf("ERROR: Failure allocate memory\n");
  } else {
    tmp->data = x;
    tmp->frequency = 1;
    tmp->parent = p;
    tmp->left = NULL;
    tmp->right = NULL;
  }

  return tmp;
}

int insert(data_t x, node_t **pp)
{
  node_t *tmp;

  if (*pp == NULL) {
    tmp = new_node(x, *pp);
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

int delete(data_t x, node_t **pp)
{
  node_t *tmp;

  while (*pp != NULL) {
    if ((*pp)->data == x) {
      if ((*pp)->frequency > 1) {
        (*pp)->frequency -= 1;
        return SUCCESS;
      } else {
        tmp = *pp;
        if (tmp->right == NULL && tmp->left == NULL) {
          *pp = NULL;
        } else if (tmp->right == NULL) {
          *pp = tmp->left;
        } else if (tmp->left == NULL) {
          *pp = tmp->right;
        } else {
          *pp = delete_min(&(tmp->right));
          (*pp)->right = tmp->right;
          (*pp)->left = tmp->left;
        }
        free(tmp);
        return SUCCESS;
      }
    } else if (x > (*pp)->data) {
      pp = &((*pp)->right);
    } else {
      pp = &((*pp)->left);
    }
  }
  return FAILURE;
}

node_t *delete_min(node_t **p)
{
  node_t *q;

  while ((*p)->left != NULL) {
    p = &((*p)->left);
  }
  q = *p;
  *p = (*p)->right;
  return q;
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

void show_inorder(node_t *p)
{
  if (p != NULL) {
    show_inorder(p->left);
    printf("%4d: %9d\n", p->data, p->frequency);
    show_inorder(p->right);
  }
}
