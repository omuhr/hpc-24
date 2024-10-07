#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (3 != argc) {
        printf("Usage: %s -aA -bB\n", argv[0]);
        return -1;
    }

    int a, b;
    size_t opt_idx;

    for (opt_idx = 1; opt_idx < argc && argv[opt_idx][0] == '-'; ++opt_idx) {
        if (3 != strlen(argv[opt_idx])) {
            printf("Usage: %s -aA -bB\n", argv[0]);
            return -1;
        }

        switch (argv[opt_idx][1]) {
        case 'a':
            a = atoi(&argv[opt_idx][2]);
            break;
        case 'b':
            b = atoi(&argv[opt_idx][2]);
            break;
        default:
            printf("Usage: %s -aA -bB\n", argv[0]);
            return -1;
        }
    }

    printf("A is %i and B is %i\n", a, b);
}
