#include <stdlib.h>
#include <assert.h>
#include "stack.h"

// Representation invariant: for all elements in the stack, `index` is equal to the next element's `index` plus one
// Representation invariant: The last element in the stack must have `index` 0
struct _s_stack
{
  stack_elem value;

  struct _s_stack *next;

  // 0 based index
  unsigned int index;
};

stack stack_empty()
{
  return NULL;
}

static struct _s_stack *node(stack_elem i)
{
  struct _s_stack *n = malloc(sizeof(struct _s_stack));
  n->next = NULL;
  n->value = i;
  return n;
}

stack stack_push(stack s, stack_elem e)
{
  struct _s_stack *n = node(e);
  n->next = s;
  n->index = s==NULL ? 0 : s->index + 1;
  return n;
}

stack stack_pop(stack s)
{
  struct _s_stack *n = s;
  s = s->next;
  free(n);
  return s;
}

unsigned int stack_size(stack s) {
  return s->index+1;
}

stack_elem stack_top(stack s) {
  return s->value;
}

bool stack_is_empty(stack s) {
  return s == NULL;
}

stack_elem *stack_to_array(stack s) {
  int slen = stack_size(s);
  stack_elem *arr = malloc(slen*sizeof(struct _s_stack));
  for(int i=slen-1; 0<=i;--i) {
    arr[i] = s->value;
    s = s->next;
  }

  return arr;
}

stack stack_destroy(stack s) {
  struct _s_stack *p;
  while(s!=NULL) {
    p = s;
    s = s->next;
    free(p);
  }
  return s;
}
