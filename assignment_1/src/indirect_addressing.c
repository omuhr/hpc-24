#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long ONE_SEC = 1e9;
int BENCH_ITS = 5e3;
int SIZE = 1e6;

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

void linear_combination_indirect(
    double x[],
    double y[],
    double a,
    size_t size
) {
    size_t p[size];
    for (size_t ix = 0; ix < size; ++ix)
        p[ix] = ix;

    for (size_t i = 0; i < size; ++i) {
        y[p[i]] += a * x[p[i]];
    }
}

void linear_combination_indirect_with_jump(
    double x[],
    double y[],
    double a,
    size_t size
) {
    size_t p[size];
    size_t size_jump = 1000;
    for (size_t jx = 0, kx = 0; jx < size_jump; ++jx)
        for (size_t ix = jx; ix < size; ix += size_jump, ++kx)
            p[ix] = kx;

    for (size_t i = 0; i < size; ++i) {
        y[p[i]] += a * x[p[i]];
    }
}

void linear_combination_direct(double x[], double y[], double a, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        y[i] += a * x[i];
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    printf("Running benchmark %s\n", argv[0]);

    double* x = (double*)malloc(SIZE * sizeof(double));
    double* y = (double*)malloc(SIZE * sizeof(double));
    for (int i = 0; i < SIZE; ++i) {
        x[i] = rand();
        y[i] = rand();
    }
    double a = (double)rand() / (double)RAND_MAX * 1e2F;

    struct timespec start_time, end_time;
    float time_per_it_ns;

    // Indirect indexing
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        linear_combination_indirect(x, y, a, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in linear_combination_indirect: %f\n", y[0]);
    printf(
        "Compute time for linear_combination_indirect: %f [ns/it]\n",
        time_per_it_ns
    );

    // Indirect indexing jump
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        linear_combination_indirect_with_jump(x, y, a, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "First element in linear_combination_indirect_with_jump: %f\n",
        y[0]
    );
    printf(
        "Compute time for linear_combination_indirect_with_jump: %f [ns/it]\n",
        time_per_it_ns
    );

    // Direct indexing
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        linear_combination_direct(x, y, a, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in linear_combination_direct: %f\n", y[0]);
    printf(
        "Compute time for linear_combination_direct: %f [ns/it]\n",
        time_per_it_ns
    );

    free(x);
    free(y);

    return 0;
}
