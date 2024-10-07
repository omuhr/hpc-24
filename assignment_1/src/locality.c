#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long ONE_SEC = 1e9;
int BENCH_ITS = 5e3;
int SIZE = 1e3;

long timespec_to_ns(struct timespec* timestamp) {
    return (timestamp->tv_sec * ONE_SEC + timestamp->tv_nsec);
}

void get_timestamp(struct timespec* timestamp) {
    /* get timestamp before */
    clock_gettime(CLOCK_MONOTONIC, timestamp);
}

long time_difference_ns(
    struct timespec* latest_time,
    struct timespec* earliest_time
) {
    return timespec_to_ns(latest_time) - timespec_to_ns(earliest_time);
}

void row_sums(double* sums, const double** matrix, size_t nrs, size_t ncs) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        double sum = 0.;
        for (size_t jx = 0; jx < ncs; ++jx)
            sum += matrix[ix][jx];
        sums[ix] = sum;
    }
}

void col_sums(double* sums, const double** matrix, size_t nrs, size_t ncs) {
    for (size_t jx = 0; jx < ncs; ++jx) {
        double sum = 0.;
        for (size_t ix = 0; ix < nrs; ++ix)
            sum += matrix[ix][jx];
        sums[jx] = sum;
    }
}

void col_sums_smart(
    double* sums,
    const double** matrix,
    size_t nrs,
    size_t ncs
) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        for (size_t jx = 0; jx < ncs; ++jx)
            sums[ix] += matrix[ix][jx];
    }
}

int main(int argc, char* argv[]) {
    printf("Running benchmark %s\n", argv[0]);

    double* elements = (double*)malloc(SIZE * SIZE * sizeof(double));
    double** matrix = (double**)malloc(SIZE * sizeof(double*));
    for (int i = 0; i < SIZE; ++i) {
        matrix[i] = elements + i * SIZE;
    }

    struct timespec start_time, end_time;
    float time_per_it_ns;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = (double)(i * SIZE + j);
        }
    }

    double* row_sum = (double*)malloc(SIZE * sizeof(double));
    double* col_sum = (double*)malloc(SIZE * sizeof(double));

    // Row sums
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        row_sums(row_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in row sums: %f\n", row_sum[0]);
    printf("Compute time for row_sums: %f [ns/it]\n", time_per_it_ns);

    // Col sums
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        col_sums(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in col sums: %f\n", col_sum[0]);
    printf("Compute time for col_sums: %f [ns/it]\n", time_per_it_ns);

    // Col sums smart
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        col_sums_smart(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in col sums smart: %f\n", col_sum[0]);
    printf("Compute time for col_sums_smart: %f [ns/it]\n", time_per_it_ns);

    free(elements);
    free(matrix);

    return 0;
}
