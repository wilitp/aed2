#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node *front;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int prio;
    struct s_node * next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    new_node->prio = priority;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    unsigned int actual_size = 0;
    // For starters, the stack value shouldn't be null;
    bool valid = (q != NULL);

    struct s_node *curr = q->front;
    while(valid && curr != NULL) {
      // Keep track of size
      ++actual_size;
      // Check order's validity
      valid = curr->next == NULL || curr->prio <= curr->next->prio;
      curr = curr->next;
    }

    return valid && q->size == actual_size;
    return true;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->front = NULL;
    q->size = 0;
    invrep(q);
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    // Node to the left
    struct s_node *left;
    // Node to the right
    struct s_node *right;
    left = NULL;
    right = q->front;

    while(right != NULL && new_node->prio >= right->prio) {
      left = right;
      right = right->next;
    }

    if(left == NULL) { // No nodes to the left
      // Add at the beginning
      new_node->next = right;
      q->front = new_node;
    } else {
      // Add in between
      left->next = new_node;
      new_node->next = right;
    }

    ++q->size;

    return q;
}

bool pqueue_is_empty(pqueue q) {
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    return q->front->prio;
}

unsigned int pqueue_size(pqueue q) {
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q));
    struct s_node *killme = q->front;
    q->front = q->front->next;
    destroy_node(killme);
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *killme = q->front;
    while(q->front != NULL) {
      killme = q->front;
      q->front = killme->next;
      destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
