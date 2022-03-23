# ifndef EJ3_ARRAY_HELPERS
# define EJ3_ARRAY_HELPERS
#include "mybool.h"

mybool array_is_sorted(int a[], unsigned int length);

unsigned int array_from_file(
  int array[],
  unsigned int max_size,
  const char *filepath);

void array_dump(int a[], unsigned int length);

#endif
