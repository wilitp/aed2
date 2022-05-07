#include "./pair.h"

pair_t pair_new(int x, int y) {
  pair_t pair = {x, y};
  return pair;
}

int pair_first(pair_t p) {
  return p.fst;
}

int pair_second(pair_t p) {
  return p.snd;
}

pair_t pair_swapped(pair_t p) {
  pair_t s = {p.snd, p.fst};
  return s;
}

pair_t pair_destroy(pair_t p) {
  return p;
}


