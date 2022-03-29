#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
  for(unsigned int j=i; 0<j; j--) {
    if(goes_before(a[j], a[j-1])) {
      swap(a, j, j-1);
    }
  }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
  unsigned int i = izq+1;
  unsigned int j = der;

  while (i<=j){
    // Si los dos estan mal ubicados
    if(goes_before(a[izq], a[i]) && goes_before(a[j], a[izq])) {
      swap(a, i, j);
      i++;
      j--;
    }
    else {
      // Si el de la izquierda esta bien ubicado
      if(goes_before(a[i], a[izq])) {
        i++;
      }
      // Si el de la derecha esta bien ubicado
      if(goes_before(a[izq], a[j])) {
        j--;
      }
    }
  }

  // Finalmente swapeamos el pivot
  swap(a, izq, j);

  return j;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
  unsigned int pivot = partition(a, izq, der); 
  if(pivot>izq) {
    quick_sort_rec(a, izq, pivot-1);
  }
  if(pivot<der) {
    quick_sort_rec(a, pivot+1, der);
  }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
