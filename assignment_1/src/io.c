#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long ONE_SEC = 1e9;
int BENCH_ITS = 1;
int INTS_TO_SUM = (1 << 20);
int SIZE = 1e6;
char HDD_DIR[] = "./hdd_data.bin";
char SSD_DIR[] = "/run/mount/scratch/hpcuser111_2024/ssd_data.bin";

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
    // srand(time(NULL));

    printf("Running benchmark %s\n", argv[0]);

    struct timespec start_time, end_time;
    float time_diff_ns;

    // Writing to HDD

    FILE* fp_w_hdd = fopen(HDD_DIR, "w");
    if (fp_w_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int i = 0; i <= INTS_TO_SUM; ++i) {
        fwrite(&i, sizeof(int), 1, fp_w_hdd);
        fflush(fp_w_hdd);
    }
    get_timestamp(&end_time);

    fclose(fp_w_hdd);

    time_diff_ns = (float)time_difference_ns(&end_time, &start_time);
    printf(
        "Written the first %d integers to HDD individually in %f [ns]\n",
        INTS_TO_SUM,
        time_diff_ns
    );

    // Reading from HDD

    FILE* fp_r_hdd = fopen(HDD_DIR, "r");
    if (fp_r_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    int integer;
    for (int i = 0; i <= INTS_TO_SUM; ++i) {
        fread(&integer, sizeof(int), 1, fp_r_hdd);
    }
    get_timestamp(&end_time);

    fclose(fp_r_hdd);

    time_diff_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from HDD individually in %f [ns]\n",
        INTS_TO_SUM,
        time_diff_ns
    );

    // Writing to SSD

    FILE* fp_w_ssd = fopen(SSD_DIR, "w");
    if (fp_w_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int i = 0; i <= INTS_TO_SUM; ++i) {
        fwrite(&i, sizeof(int), 1, fp_w_ssd);
        fflush(fp_w_ssd);
    }
    get_timestamp(&end_time);

    fclose(fp_w_ssd);

    time_diff_ns = (float)time_difference_ns(&end_time, &start_time);
    printf(
        "Written the first %d integers to SSD individually in %f [ns]\n",
        INTS_TO_SUM,
        time_diff_ns
    );

    // Reading from SSD

    FILE* fp_r_ssd = fopen(SSD_DIR, "r");
    if (fp_r_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int i = 0; i <= INTS_TO_SUM; ++i) {
        fread(&integer, sizeof(int), 1, fp_r_ssd);
    }
    get_timestamp(&end_time);

    fclose(fp_r_ssd);

    time_diff_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from SSD individually in %f [ns]\n",
        INTS_TO_SUM,
        time_diff_ns
    );

    return 0;
}
