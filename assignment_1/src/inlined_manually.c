#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long ONE_SEC = 1e9;
int SUM_TO = 200e3;
int SIZE = 30e3;

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

void populate_double_array(double arr[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand();
    }
}

int main() {
    srand(time(NULL));

    struct timespec start_time, end_time;
    float time_per_it_ns;

    double as_re[SIZE];
    double as_im[SIZE];
    double bs_re[SIZE];
    double bs_im[SIZE];
    double cs_re[SIZE];
    double cs_im[SIZE];

    populate_double_array(bs_re);
    populate_double_array(bs_im);
    populate_double_array(cs_re);
    populate_double_array(cs_im);

    get_timestamp(&start_time);
    for (int idx = 1; idx <= SUM_TO; ++idx) {
        for (int i = 0; i < SIZE; ++i) {
            as_re[i] = (bs_re[i] * cs_re[i]) - (bs_im[i] * cs_im[i]);
            as_im[i] = (bs_re[i] * cs_im[i]) + (bs_im[i] * cs_re[i]);
        }
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)SUM_TO;
    printf("Compute time: %f [ns/it]\n", time_per_it_ns);

    int random_index = rand() % (SIZE + 1);

    printf("%f + %fi\n", as_re[random_index], as_im[random_index]);

    return 0;
}
