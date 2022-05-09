#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "./stack.h"

typedef struct s_tree_t{
  void *value;
  struct s_tree_t *left;
  struct s_tree_t *right;
} tree_t;




/* void dft(void *pfun, tree_t t) { */
/* } */

int main(void) {
  stack_t s = empty_stack();

}


