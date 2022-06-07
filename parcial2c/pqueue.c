#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node ** elems;
    unsigned int size;
    priority_t min_priority;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->next = NULL;
    new_node->elem = e;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pqueue q) {
    // Pqueue value shouldn't be null unless destroyed
    bool valid = q!=NULL;
    struct s_node *curr;

    // Check size corresponds to the actual amount of elements
    if(valid) {
        unsigned int actual_size = 0;
        for(unsigned int i = 0; i<=q->min_priority; ++i) {
            curr = q->elems[i];
            while(curr != NULL) {
                ++actual_size;
                curr = curr->next;
            }
        }
        valid = actual_size == q->size;
    }
    return valid;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->min_priority = min_priority;
    q->elems = malloc(sizeof(struct s_node*) * (min_priority+1));
    for(unsigned int i=0; i<=min_priority; i++) {
        q->elems[i] = NULL;
    }
    assert(invrep(q));
    assert(pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));


    struct s_node *new_node = create_node(e);
    
    if(q->elems[priority] == NULL) {
        q->elems[priority] = new_node;
    } else {
        // Get the queue for the given priority
        struct s_node *curr = q->elems[priority];
        // Insert the element at the end of the queue
        while(curr->next != NULL) {
            curr = curr->next;
        } 
        curr->next = new_node;
    }
    ++q->size;

    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem peek;
    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        if(q->elems[i] != NULL) {
            peek = q->elems[i]->elem;
            break;
        }
    }

    return peek;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t peek_prio;

    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        if(q->elems[i] != NULL) {
            peek_prio = i;
            break;
        }
    }

    return peek_prio;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t peek_prio = pqueue_peek_priority(q);
    // Asume q->elems[peek_prio] is not NULL, given peuque_peek_priority works properly
    struct s_node *killme = q->elems[peek_prio];
    q->elems[peek_prio] = q->elems[peek_prio]->next;
    destroy_node(killme);
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *killme;
    for(unsigned int i = 0; i<=q->min_priority; ++i) {
        while(q->elems[i] != NULL) {
            killme = q->elems[i];
            q->elems[i] = q->elems[i]->next;
            destroy_node(killme);
        }
    }
    free(q->elems);
    free(q);
    q = NULL;
    return q;
}

