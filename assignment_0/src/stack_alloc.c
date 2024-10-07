#include <stdio.h>

int main() {
    // sizeof(int) == 4
    // this corresponds to 4 * 3e6 bytes being allocated
    // which is 12e6 bytes
    // which is 12Mb
    // the stack isn't larger than that
    size_t size = 3e6;

    int as[size];
    for (size_t ix = 0; ix < size; ++ix)
        as[ix] = 1;

    printf("%d\n", as[0]);

    return 0;
}
