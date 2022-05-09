
typedef struct s_stack_t * stack_t;

stack_t empty_stack();

stack_t push(stack_t s, void *el);

stack_t pop(stack_t s);

void *top(stack_t s);
