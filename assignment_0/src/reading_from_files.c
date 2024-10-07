#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size = 10;

    {
        FILE* fp = fopen("./matrix.mat", "r");
        if (fp == NULL) {
            printf("Error while requesting file handle: %s\n", strerror(errno));
            return -1;
        }

        int expected_element;
        int cur_element;
        int count = 0;
        while (fscanf(fp, "%d", &cur_element) && !feof(fp)) {
            int expected_ix = count / size;
            int expected_jx = count % size;
            expected_element = expected_ix * expected_jx;

            if (cur_element != expected_element) {
                printf(
                    "Expected M[%.2d, %.2d] = %.2d, but got M[%.2d, %.2d] = "
                    "%.2d. "
                    "Exiting...\n",
                    expected_ix,
                    expected_jx,
                    expected_element,
                    expected_ix,
                    expected_jx,
                    cur_element
                );
                return -1;
            }

            count++;
        }

        fclose(fp);
    }
}
