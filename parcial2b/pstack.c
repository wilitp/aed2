#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
  unsigned int size;
  struct s_node * front;
};

struct s_node {
  struct s_node * next;
  priority_t prio;
  pstack_elem elem;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->prio = priority;
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    unsigned int actual_size = 0;
    // For starters, the stack value shouldn't be null;
    bool valid = (s != NULL);

    struct s_node *curr = s->front;
    while(valid && curr != NULL) {
      // Keep track of size
      ++actual_size;
      // Check order's validity
      valid = curr->next == NULL || curr->prio >= curr->next->prio;
      curr = curr->next;
    }

    return valid && s->size == actual_size;
}

pstack pstack_empty(void) {
    pstack s=malloc(sizeof(struct s_pstack));
    s->front = NULL;
    s->size = 0;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    // New node to add
    struct s_node *new_node = create_node(e, priority);
    // Node to the left
    struct s_node *left;
    // Node to the right
    struct s_node *right;
    left = NULL;
    right = s->front;

    while(right != NULL && new_node->prio < right->prio) {
      left = right;
      right = right->next;
    }

    if(left == NULL) { // No nodes to the left
      // Add at the beginning
      new_node->next = right;
      s->front = new_node;
    } else {
      // Add in between
      left->next = new_node;
      new_node->next = right;
    }
    ++s->size;

    assert(invrep(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s));
    assert(s->front != NULL);
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(s->front != NULL);
    return s->front->prio;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s));
    struct s_node *killme = s->front;
    s->front = s->front->next;
    destroy_node(killme);
    --s->size;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *killme = s->front;
    while(s->front != NULL) {
      killme = s->front;
      s->front = killme->next;
      destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

