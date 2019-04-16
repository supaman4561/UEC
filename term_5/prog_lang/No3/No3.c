#include <stdio.h>
#include <stdlib.h>

#define EQUA_MAX 100
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef char data_t;
typedef enum {EQUAL, RPAREN, ADDSUB, MULDIV, LPAREN, OPERAND} token_t;
typedef struct node_tag {
  data_t data;
  struct node_tag *next;
}node_t;

void reverse_polish(char equation[]);
token_t token_priority(data_t x);
node_t *node_new(data_t x, node_t *p);
int has_any(node_t *p);
int push(data_t x, node_t **pp);
node_t *pop(node_t **pp);

/* for debug */
void show_stack(node_t *p);

int main(void)
{
  char equation[EQUA_MAX];
  
  scanf("%s", equation);

  reverse_polish(equation);

  printf("%s\n", equation);
  
  return 0;
}

void reverse_polish(char equation[])
{
  node_t *head, *tmp;
  data_t token;
  token_t token_type;
  int i, j;

  /* initialize */
  head = NULL;
  i = 0;
  j = 0;
  
  while (equation[i] != '\0') {
    
    token = equation[i];

    while (has_any(head) && token_priority(head->data) != LPAREN
	   && token_priority(head->data) >= token_priority(token)) {
      tmp = pop(&head);
      equation[j++] = tmp->data;
      free(tmp);
    }
    
    if (token_priority(token) != RPAREN) {
      push(token, &head);
    } else {
      tmp = pop(&head); /* get '(' */
      free(tmp);
    }

    i++;
  }

  while (has_any(head)) {
    tmp = pop(&head);
    equation[j++] = tmp->data;
    free(tmp);
  }

  while (j < i) {
    equation[j++] = '\0';
  }
}

token_t token_priority(data_t x)
{
  token_t priority;
  switch (x) {
  case '=': priority = EQUAL; break;
  case '+':
  case '-': priority = ADDSUB; break;
  case '*':
  case '/': priority = MULDIV; break;
  case '(': priority = LPAREN; break;
  case ')': priority = RPAREN; break;
  default: priority = OPERAND; break;
  }

  return priority;
}

int has_any(node_t *p)
{
  if (p != NULL) {
    return TRUE;
  } else {
    return FALSE;
  }
}

node_t *node_new(data_t x, node_t *p)
{
  node_t *tmp;

  tmp = (node_t *)malloc(sizeof(node_t));
  if (tmp == NULL) {
    printf("ERROR: Failure allocate memory\n");
  } else {
    tmp->data = x;
    tmp->next = p;
  }

  return tmp;
}

int push(data_t x, node_t **pp)
{
  node_t *tmp;

  tmp = node_new(x, *pp);
  if (tmp == NULL) {
    return FAILURE;
  }

  *pp = tmp;
  return SUCCESS;
}

node_t *pop(node_t **pp)
{
  node_t *tmp;
  
  if (*pp != NULL) {
    tmp = *pp;
    *pp = (*pp)->next;
    return tmp;
  }
}


void show_stack(node_t *p)
{
  while (p != NULL) {
    printf("%c", p->data);
    p = p->next;
  }
  printf("\n");
}
