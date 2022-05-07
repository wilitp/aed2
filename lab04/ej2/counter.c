#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
  return malloc(sizeof(struct _counter));
}

void counter_inc(counter c) {
  c->count++;
}

bool counter_is_init(counter c) {
  return c->count == 0;
}

void counter_dec(counter c) {
  assert(!counter_is_init(c));
  c->count--;
}

counter counter_copy(counter c) {
  counter cp = malloc(sizeof(struct _counter));
  cp->count = c->count;
  return cp;
}

void counter_destroy(counter c) {
  free(c);
}
