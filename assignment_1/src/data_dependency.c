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

void row_sums_unrolled2(
    double* sums,
    const double** matrix,
    size_t nrs,
    size_t ncs
) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        double sum0 = 0.;
        double sum1 = 0.;
        for (size_t jx = 0; jx < ncs; jx += 2) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx + 1];
        }
        sums[ix] = sum0 + sum1;
    }
}

void row_sums_unrolled4(
    double* sums,
    const double** matrix,
    size_t nrs,
    size_t ncs
) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        double sum0 = 0.;
        double sum1 = 0.;
        double sum2 = 0.;
        double sum3 = 0.;
        for (size_t jx = 0; jx < ncs; jx += 4) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx + 1];
            sum2 += matrix[ix][jx + 2];
            sum3 += matrix[ix][jx + 3];
        }
        sums[ix] = sum0 + sum1 + sum2 + sum3;
    }
}

void row_sums_unrolled8(
    double* sums,
    const double** matrix,
    size_t nrs,
    size_t ncs
) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        double sum0 = 0.;
        double sum1 = 0.;
        double sum2 = 0.;
        double sum3 = 0.;
        double sum4 = 0.;
        double sum5 = 0.;
        double sum6 = 0.;
        double sum7 = 0.;
        for (size_t jx = 0; jx < ncs; jx += 8) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx + 1];
            sum2 += matrix[ix][jx + 2];
            sum3 += matrix[ix][jx + 3];
            sum4 += matrix[ix][jx + 4];
            sum5 += matrix[ix][jx + 5];
            sum6 += matrix[ix][jx + 6];
            sum7 += matrix[ix][jx + 7];
        }
        sums[ix] = sum0 + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7;
    }
}

void row_sums_unrolled4_array(
    double* sums,
    const double** matrix,
    size_t nrs,
    size_t ncs
) {
    for (size_t ix = 0; ix < nrs; ++ix) {
        double unrolled_sums[4] = { 0., 0., 0., 0. };
        for (size_t jx = 0; jx < ncs; jx += 4) {
            unrolled_sums[0] += matrix[ix][jx];
            unrolled_sums[1] += matrix[ix][jx + 1];
            unrolled_sums[2] += matrix[ix][jx + 2];
            unrolled_sums[3] += matrix[ix][jx + 3];
        }
        sums[ix] = unrolled_sums[0] + unrolled_sums[1] + unrolled_sums[2]
            + unrolled_sums[3];
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
    printf("First element in row sums: %f.0\n", row_sum[0]);
    printf("Compute time for row_sums: %f [ns/it]\n", time_per_it_ns);

    // Row sums unrolled 2
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        row_sums_unrolled2(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in row sums unrolled2: %f.0\n", col_sum[0]);
    printf("Compute time for row_sums_unrolled2: %f [ns/it]\n", time_per_it_ns);

    // Row sums unrolled 4
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        row_sums_unrolled4(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in row sums unrolled4: %f.0\n", col_sum[0]);
    printf("Compute time for row_sums_unrolled4: %f [ns/it]\n", time_per_it_ns);

    // Row sums unrolled 8
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        row_sums_unrolled8(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in row sums unrolled8: %f.0\n", col_sum[0]);
    printf("Compute time for row_sums_unrolled8: %f [ns/it]\n", time_per_it_ns);

    // Row sums unrolled 4 array
    get_timestamp(&start_time);
    for (int idx = 1; idx <= BENCH_ITS; ++idx) {
        row_sums_unrolled4_array(col_sum, (const double**)matrix, SIZE, SIZE);
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf("First element in row sums unrolled4 array: %f.0\n", col_sum[0]);
    printf(
        "Compute time for row_sums_unrolled4_array: %f [ns/it]\n",
        time_per_it_ns
    );

    free(elements);
    free(matrix);

    return 0;
}
