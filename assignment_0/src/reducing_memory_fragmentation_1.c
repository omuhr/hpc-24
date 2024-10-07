#include <stdio.h>
#include <stdlib.h>

int main() {
  int size = 10;

  // the memory allocated to contain all matrix elements
  // this will be contiguous memory
  // asentries is a pointer to the start of the memory chunck
  int *asentries = (int *)malloc(sizeof(int) * size * size);
  // here we allocated memory for size number of int pointer
  // as is a pointer to the start of the memory chunck containing said pointers
  int **as = (int **)malloc(sizeof(int *) * size);

  // we shift/set each pointer we just allocated to point "to the right" of the
  // start of the large chunck, each pointer separated by the size of a row.
  // in other words; we set each pointer at the start of a row in the matrix
  for (size_t ix = 0, jx = 0; ix < size; ++ix, jx += size)
    as[ix] = asentries + jx;

  // we may now use subscript notation to index the matrix
  for (size_t ix = 0; ix < size; ++ix)
    for (size_t jx = 0; jx < size; ++jx)
      as[ix][jx] = 0;

  printf("%d\n", as[0][0]);

  free(as);
  free(asentries);
}

// with this strategy we guarantee that all elements of our matrix are allocated
// next to echother in memory, which is performant
