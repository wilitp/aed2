typedef struct s_set_t * set_t;

set_t empty_set();

set_t set_add(set_t set, void *el);

bool includes(set_t set, void *el);
