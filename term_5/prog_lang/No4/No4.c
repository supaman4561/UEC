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
typedef enum {INSERT, DELETE, SHOW, QUIT} command_t;

node_t *new_node(data_t x);
int insert(data_t x, node_t **pp);
int delete(data_t x, node_t **pp);
node_t *is_member(data_t x, node_t *p);
node_t *min_node(node_t *p);
node_t *max_node(node_t *p);
void show_inorder(node_t *p);

int main(void)
{
  node_t *root, *tmp;
  data_t num;
  int command;

  /* initialize */
  root = NULL;
  
  printf("===commands===\n");
  printf("0: insert\n");
  printf("1: delete\n");
  printf("2: show\n");
  printf("3: quit\n");
  
  do {
    printf("command>");
    scanf("%d", &command);
    
    if (command == INSERT) {
      
      printf("data>");
      scanf("%d", &num);

      if ((tmp = is_member(num, root)) == NULL) {
	if (insert(num, &root) == FAILURE) {
	  printf("Failed to insert new node.\n");
	}
      } else {
	tmp->frequency += 1;
      }
      
    } else if (command == DELETE) {

      printf("data>");
      scanf("%d", &num);

      if ((tmp = is_member(num, root)) == NULL) {
	printf("The data is not exist.\n");
      } else {
	if (tmp->frequency == 1) {
	  if (delete(num, &root) == FAILURE) {
	    printf("Failed to remove node.\n");
	  }
	} else {
	  tmp->frequency -= 1;
	}
      }

    } else if (command == SHOW) {

      printf("data: frequency\n");
      show_inorder(root);

    } else if (command == QUIT){

      printf("Bye!\n");
      
    } else {

      printf("Invalid command\n");

    }
    
  }while (command != QUIT);

  
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

int delete(data_t x, node_t **pp)
{
  node_t *tmp, *prev;
  
  if (*pp == NULL) {
    return FAILURE;
  } else {
    if ((*pp)->data == x) {
      if ((*pp)->right != NULL) {
	tmp = min_node((*pp)->right);
      } else if ((*pp)->left != NULL) {
	tmp = max_node((*pp)->left);
      } else {
	tmp = *pp;
      }
      (*pp)->data = tmp->data;
      free(tmp);
    }
    return SUCCESS;
  }
}

node_t *min_node_prev(node_t *p)
{
  while (p->left != NULL) {
    p = p->left;
  }
  return p;
}

node_t *max_node(node_t *p)
{
  while (p->right != NULL) {
    p = p->right;
  }
  return p;
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
