#include "assert.h"
#include <stdbool.h>
#include <stdlib.h>

#include "./list.h"

struct s_node_t {
  elem value;
  struct s_node_t *next;
};

list empty() {
  return NULL;
}

list addl(list l, elem e) {
  struct s_node_t *n;
  n = malloc(sizeof(struct s_node_t));
  n->next = l;
  n->value = e;
  return n;
}

list addr(list l, elem e) {
  list n;
  n = malloc(sizeof(struct s_node_t));
  n->value = e;
  n->next = NULL;
  if(l != NULL) {
    list i;
    i = l;
    while(i->next != NULL) {
      i = i->next;
    }
    i->next = n;
  } else {
    l = n;
  }

  return l;
}

bool is_empty(list l) {
  return l == NULL;
}

elem list_index(list l, unsigned int i) {
  assert(i < length(l));
  list p = l;
  unsigned int c = 0;
  while(c<i) {
    p = p->next;
    c++;
  }
  return p->value;
}

void _exhaust_into(list src, list target) {
  list p = src;
  while(p!=NULL) {
    addr(target, p->value);
  }
}

list copy(list l) {
  list lc = empty();
  _exhaust_into(l, lc);
  return lc;
}

list concat(list l1, list l2) {
  list res = empty();
  _exhaust_into(l1, res);
  _exhaust_into(l2, res);
  return res;
}

list tail(list l) {
  assert(!is_empty(l));
  return l->next;
}

elem head(list l) {
  assert(!is_empty(l));
  return l->value;
}

unsigned int length(list l) {
  unsigned int res = 0;
  list p = l;
  while(p != NULL) {
    p = p->next;
    res++;
  }
  return res;
}

list drop(list l, unsigned int n) {
  assert(n<=length(l));
  while(n>0) {
    l = l->next;
    n--;
  }

  return l;
}

list list_destroy(list l) {
  if(l != NULL) {
    list a, b;
    a = l;
    b = a->next;
    while(a != NULL) {
      free(a);
      a = b;
      if(a != NULL) {
        b = a->next;
      }
    }
    l = a;
  }
  return l;
}
