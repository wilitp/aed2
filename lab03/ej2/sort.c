/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return x.rank <= y.rank;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int j, unsigned int i){
  player_t tmp;
  tmp = a[j];
  a[j] = a[i];
  a[i] = tmp;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
  unsigned int i = izq+1;
  unsigned int j = der;

  while (i<=j){
    // Si los dos estan mal ubicados
    if(!goes_before(a[i], a[izq]) && !goes_before(a[izq], a[j])) {
      swap(a, i, j);
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

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
  unsigned int pivot = partition(a, izq, der); 
  if(pivot>izq) {
    quick_sort_rec(a, izq, pivot-1);
  }
  if(pivot<der) {
    quick_sort_rec(a, pivot+1, der);
  }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
