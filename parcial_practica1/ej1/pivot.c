#include <stdbool.h>
#include <stdio.h>

#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
  bool b = true;

  // Veo que los anteriores sean menores iguales
  for(unsigned int i=0; i<piv && b; i++) {
    if(array[i] > array[piv]) {
      b = false;
    }
  }

  // Veo que los siguientes sean mayores estrictos
  for(unsigned int i=piv+1; i<length && b; i++) {
    if(array[i] <= array[piv]) {
      b = false;
    }
  }
  return b;
}

/* int main(void) { */
/*   int arr[] = {8,7,8,16,15}; */
/*   printf("%d", is_pivot(arr, 5, 0)); */
/* } */
