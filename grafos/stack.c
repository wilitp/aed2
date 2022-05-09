#include <stdlib.h>

typedef struct s_stack_t {
  void *value;
  struct s_stack_t *next;
} stack_node_t;

typedef struct s_stack_t * stack_t;

stack_t empty_stack() {
  return NULL;
}

stack_t push(stack_t s, void *el) {
  stack_t node;
  node = malloc(sizeof(stack_node_t));
  node->next = s;
  node->value = el;
  return node;
}

stack_t pop(stack_t s) {
  stack_t next = s->next;
  free(s);
  return next;
}

void *top(stack_t s) {
  return s->value;
}
