#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void insert(int a[], unsigned int i) {
  for(unsigned int j=i; 0<j; j--) {
    if(goes_before(a[j], a[j-1])) {
      swap(a, j, j-1);
    } else {
      break;
    }
  }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        // Checkeo el invariante: los elementos anteriores a a[i] estan ordenados
        assert(array_is_sorted(a,i));
        insert(a, i);
    }
}
