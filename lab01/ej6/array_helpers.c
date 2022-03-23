/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void array_swap(int a[], unsigned int i, unsigned int j) {
  if(i!=j) {
    int tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
}

void array_reverse(int a[], unsigned int length) {
  unsigned int pos = (length / 2) + 1;

  for(;pos< length; pos++) {
    array_swap(a, length-1-pos, pos);

  }
}

bool array_is_sorted(int a[], unsigned int length) 
{
  bool r = true;
  for(unsigned int i=0; i<(length-1);i++) {
    if(a[i] > a[i+1]) {
      r = false;
      break;
    }
  }
  return r;
}

unsigned int array_from_file(
  int array[],
  unsigned int max_size,
  const char *filepath) 
{
  // Abro el archivo
  FILE *f;
  f = fopen(filepath, "r");
  // Consigo su tamanio
  unsigned int length;
  fscanf(f, "%u", &length);

  // Corto la length en el max size si este es menor
  if(max_size < length){
    length = max_size;
  }

  // Voy leyendo y agregando los numeros
  for(unsigned int i=0;i<length;i++){
    fscanf(f, "%d", &array[i]);
  }
  fclose(f);
  return length;

}

void array_dump(int a[], unsigned int length) {
  printf("[");
  for(unsigned int i=0; i<length; i++) 
  {
    if(i != length-1 ){
      printf(" %d,", a[i]);
    }
    else {
      printf(" %d", a[i]);
    }
  }
  printf("]\n");
}
