# ifndef EJ3_ARRAY_HELPERS
# define EJ3_ARRAY_HELPERS
#include <stdbool.h>

void array_swap(int a[], unsigned int i, unsigned int j);

void array_reverse(int a[], unsigned int length);

bool array_is_sorted(int a[], unsigned int length);

unsigned int array_from_file(
  int array[],
  unsigned int max_size,
  const char *filepath);

void array_dump(int a[], unsigned int length);

#endif
