#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size = 10;

    int* asentries = (int*)malloc(sizeof(int) * size * size);
    int** as = (int**)malloc(sizeof(int*) * size);

    for (size_t ix = 0, jx = 0; ix < size; ++ix, jx += size)
        as[ix] = asentries + jx;

    for (size_t ix = 0; ix < size; ++ix)
        for (size_t jx = 0; jx < size; ++jx)
            as[ix][jx] = ix * jx;

    printf("%d\n", as[0][0]);

    {
        FILE* fp = fopen("./matrix.mat", "w");
        if (fp == NULL) {
            printf("Error while requesting file handle: %s\n", strerror(errno));
        }

        for (size_t ix = 0; ix < size; ++ix) {
            for (size_t jx = 0; jx < size - 1; ++jx) {
                fprintf(fp, "%.2d ", as[ix][jx]);
            }
            fprintf(fp, "%.2d\n", as[ix][size - 1]);
        }

        fclose(fp);
    }
    free(as);
    free(asentries);
}
