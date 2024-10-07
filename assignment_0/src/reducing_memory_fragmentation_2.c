#include <stdio.h>
#include <stdlib.h>

int main() {
  int size = 10;

  // here we allocate memory for size number of pointers and as points to the
  // start of the allocated chunck
  int **as = (int **)malloc(sizeof(int *) * size);

  // we then allocate memory for size number of ints in contiguous memory, a row
  // in the matrix
  // we do this for each row separately, not guaranteeing that any two rows are
  // nearby in memory
  // in other words; memory is framented
  for (size_t ix = 0; ix < size; ++ix)
    as[ix] = (int *)malloc(sizeof(int) * size);

  // the ergonomics of indexing the array are the same in either case
  for (size_t ix = 0; ix < size; ++ix)
    for (size_t jx = 0; jx < size; ++jx)
      as[ix][jx] = 0;

  printf("%d\n", as[0][0]);

  // we must make sure that we free each row separately
  for (size_t ix = 0; ix < size; ++ix)
    free(as[ix]);
  free(as);
}

// with this strategy we do not guarantee that all elements of our matrix are
// allocated next to echother in memory, which may be useful if the matrix is
// large or we are otherwise constrained for chuncks of free memory
