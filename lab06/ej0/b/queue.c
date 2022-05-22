#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

struct s_queue {
    unsigned int len;
    struct s_node *last; 
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL && 
           // first y last son los dos nulos o los dos no nulos
           ((q->first == NULL && q-> last == NULL) ||
           (q->first != NULL && q-> last != NULL));
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue));
    q->first = NULL;
    q->last = NULL;
    q->len = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if(q->first == NULL) {
      q->first = (q->last = new_node);
    } else {
      q->last->next = new_node;
      q->last = new_node;
    }

    ++q->len;
    assert(invrep(q));
    assert(!queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    return q->len;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));

    struct s_node * killme=q->first;
    q->first = q->first->next;
    // Si el ultimo es tambien el primero, tambien lo destruimos
    if(q->last == killme) {
      q->last = NULL;
    }
    killme = destroy_node(killme);

    --(q->len);
    assert(invrep(q));

    return q;

}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

