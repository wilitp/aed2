#include "./set.h"
#include <stdbool.h>

struct s_set_t {
  void *el;
  struct s_set_t *next;
};

set_t empty_set();

set_t set_add(set_t set, void *el);

bool includes(set_t set, void *el);
