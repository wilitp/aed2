# ifndef EJ3_ARRAY_HELPERS
# define EJ3_ARRAY_HELPERS
unsigned int array_from_file(
  int array[],
  unsigned int max_size,
  const char *filepath);


void array_dump(int a[], unsigned int length);
#endif
