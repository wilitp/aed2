#include <stdbool.h>
#include <stdio.h>

#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
  bool b = true;
  if(length > 3) {
    for(unsigned int i=1; i < length-2 && length; i+=2) {
      if(array[i] > array[i+2]) {
        b = false;
      }
    }
  }

  return b;
}


/* int main(void) { */
/*   int arr[] = {10,7,8,4,5}; */
/*   printf("%d", is_odd_sorted(arr, 5)); */
/* } */
