/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include "mybool.h"
#include <stdio.h>
#include <stdlib.h>

mybool array_is_sorted(int a[], unsigned int length) 
{
  mybool r = true;
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
