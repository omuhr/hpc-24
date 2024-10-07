#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * We see that the runtime varies between each optimization level.
 * The different optimization levels balance the ammount of time spent compiling
 * the executable with its performance as well as how debug information should
 * be kept track off and exposed to debug tools like gdb.
 * The performance of the executable is also a balance between the size of the
 * executable, the execution time of the program, as well as how much memory the
 * program uses.
 **/

long ONE_SEC = 1e9;
int SUM_TO = 1e9;

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

int main(int argc, char* argv[]) {
    struct timespec start_time, end_time;
    float time_per_it_ns;

    get_timestamp(&start_time);
    long sum = 0;
    for (int idx = 1; idx <= SUM_TO; ++idx) {
        sum += idx;
    }
    get_timestamp(&end_time);
    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)SUM_TO;
    printf("Result: %li\nCompute time: %f [ns/it]\n", sum, time_per_it_ns);
}
