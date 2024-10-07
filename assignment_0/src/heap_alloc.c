#include <stdio.h>
#include <stdlib.h>

int main() {
    // doesn't segfault as the heap is larger than the stack
    int size = 3e6;

    int* as = (int*)malloc(sizeof(int) * size);
    for (size_t ix = 0; ix < size; ++ix)
        as[ix] = 1;

    printf("%d\n", as[0]);

    free(as);
}
