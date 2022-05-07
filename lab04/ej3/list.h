#include <stdbool.h>

typedef int elem;
typedef struct s_node_t * list;

list empty();
/* Returns an empty list */

list addl(list l, elem e);
/* Adds element to list at the first position */

list addr(list l, elem e);
/* Adds element to list at the last position */

bool is_empty(list l);
/* Is the list empty? */

elem list_index(list l, unsigned int i);
/* Returns the element at position i */

list copy(list l);
/* Returns a copy of the provided list */

list concat(list l1, list l2);
/* Returns a list with the elements of l2 at the end of l1 */

list tail(list l);
/* Returns the tail of the list 
 * PRE: !is_empty(list)
 * */

elem head(list l);
/* Returns the first element of the list
 * PRE: !is_empty(list)
 * */

unsigned int length(list l);
/* Length of a list */

list drop(list l, unsigned int n);
/* Drop n items
 * PRE: n <= length(l) 
 * */

list list_destroy(list l);
