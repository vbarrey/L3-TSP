#include "heap.h"
#include <stdlib.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->array = malloc((k+1)*sizeof(void*));
  h->n = 0;
  h->nmax = k;
  h->f = f;
  return h;
}

void heap_destroy(heap h) {
  free(h->array);
  free(h);
  h = NULL;
}

bool heap_empty(heap h) {
  return h->n == 0;
}

bool heap_add(heap h, void *object) {
  if(h->n > h->nmax){
    return true;
  }

  int iFils = h->n + 1;
  h->array[iFils] = object;

  if(!heap_empty(h)){
    int iPere = (iFils/2 == 0) ? 1 : iFils/2;
    while(h->f(h->array[iFils], h->array[iPere])<0){
      void* tmp = h->array[iFils];
      h->array[iFils] = h->array[iPere];
      h->array[iPere] = tmp;
      iFils = iPere;
      iPere = (iFils/2 == 0) ? 1 : iFils/2;
    }
  }

  h->n++;
  return false;
}

void *heap_top(heap h) {
  if(heap_empty(h)){
    return NULL;
  }
  return h->array[1];
}

void *heap_pop(heap h) {

  void *poped = heap_top(h);

  if(poped){
    h->array[1] = h->array[h->n--];
    int i=1;

    while(true){
      int j = 2*i;
      if(j>h->n) break;

      if(j+1<= h->n && h->f(h->array[j], h->array[j+1]) > 0) j++;

      if(h->f(h->array[i], h->array[j]) < 0) break;

      void *tmp = h->array[i];
      h->array[i] = h->array[j];
      h->array[j] = tmp;
      i=j;
    }

  }
  return poped;
}
