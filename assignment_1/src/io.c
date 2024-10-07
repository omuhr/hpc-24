#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long ONE_SEC = 1e9;
int BENCH_ITS = 1;
int N_INTS = (1 << 20);
int SIZE = 1e6;
char HDD_INDIVIDUAL_DIR[] = "./hdd_data_individually.bin";
char SSD_INDIVIDUAL_DIR[]
    = "/run/mount/scratch/hpcuser111_2024/ssd_data_individually.bin";
char HDD_ARRAY_DIR[] = "./hdd_data_array.bin";
char SSD_ARRAY_DIR[] = "/run/mount/scratch/hpcuser111_2024/ssd_data_array.bin";

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
    float time_per_it_ns;

    int integer_to_read;
    int* integers_to_read = (int*)malloc(N_INTS * sizeof(int));
    int* integers_to_write = (int*)malloc(N_INTS * sizeof(int));
    for (int i = 0; i < N_INTS; ++i) {
        integers_to_write[i] = i;
    }

    // DEALING WITH INDIVIDUAL INTEGERS

    // Writing to HDD individually

    FILE* fp_w_hdd = fopen(HDD_INDIVIDUAL_DIR, "w");
    if (fp_w_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        for (int i = 0; i <= N_INTS; ++i) {
            fwrite(&integers_to_write[i], sizeof(int), 1, fp_w_hdd);
            fflush(fp_w_hdd);
        }
    }
    get_timestamp(&end_time);

    fclose(fp_w_hdd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Written the first %d integers to HDD individually in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Reading from HDD individually

    FILE* fp_r_hdd = fopen(HDD_INDIVIDUAL_DIR, "r");
    if (fp_r_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        for (int i = 0; i <= N_INTS; ++i) {
            fread(&integer_to_read, sizeof(int), 1, fp_r_hdd);
        }
    }
    get_timestamp(&end_time);

    fclose(fp_r_hdd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from HDD individually in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Writing to SSD individually

    FILE* fp_w_ssd = fopen(SSD_INDIVIDUAL_DIR, "w");
    if (fp_w_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        for (int i = 0; i <= N_INTS; ++i) {
            fwrite(&integers_to_write[i], sizeof(int), 1, fp_w_ssd);
            fflush(fp_w_ssd);
        }
    }
    get_timestamp(&end_time);

    fclose(fp_w_ssd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Written the first %d integers to SSD individually in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Reading from SSD individually

    FILE* fp_r_ssd = fopen(SSD_INDIVIDUAL_DIR, "r");
    if (fp_r_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        for (int i = 0; i <= N_INTS; ++i) {
            fread(&integer_to_read, sizeof(int), 1, fp_r_ssd);
        }
    }
    get_timestamp(&end_time);

    fclose(fp_r_ssd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from SSD individually in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // DEALING WITH ARRAYS

    // Writing to HDD as array

    FILE* fp_w_array_hdd = fopen(HDD_ARRAY_DIR, "w");
    if (fp_w_array_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        fwrite(integers_to_write, sizeof(int), N_INTS, fp_w_array_hdd);
        fflush(fp_w_array_hdd);
    }
    get_timestamp(&end_time);

    fclose(fp_w_array_hdd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Written the first %d integers to HDD as array in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Reading from HDD as array

    FILE* fp_r_array_hdd = fopen(HDD_ARRAY_DIR, "r");
    if (fp_r_array_hdd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        fread(integers_to_read, sizeof(int), N_INTS, fp_r_array_hdd);
    }
    get_timestamp(&end_time);

    fclose(fp_r_array_hdd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from HDD as array in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Writing to SSD as array

    FILE* fp_w_array_ssd = fopen(SSD_ARRAY_DIR, "w");
    if (fp_w_array_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        fwrite(&integers_to_write, sizeof(int), N_INTS, fp_w_array_ssd);
        fflush(fp_w_array_ssd);
    }
    get_timestamp(&end_time);

    fclose(fp_w_array_ssd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Written the first %d integers to SSD as array in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Reading from SSD as array

    FILE* fp_r_array_ssd = fopen(SSD_ARRAY_DIR, "r");
    if (fp_r_array_ssd == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        fread(&integers_to_read, sizeof(int), N_INTS, fp_r_array_ssd);
        printf("READ INTEGERS ARRAY\n");
    }
    get_timestamp(&end_time);

    fclose(fp_r_array_ssd);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "Read the first %d integers from SSD as array in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    // Reading from SSD as array

    FILE* fpp = fopen(SSD_ARRAY_DIR, "r");
    if (fpp == NULL) {
        printf("Error while requesting file handle: %s\n", strerror(errno));
    }

    get_timestamp(&start_time);
    for (int idx; idx < BENCH_ITS; ++idx) {
        fread(&integers_to_read, sizeof(int), N_INTS, fpp);
        printf("READ INTEGERS ARRAY\n");
    }
    get_timestamp(&end_time);

    fclose(fpp);

    time_per_it_ns
        = (float)time_difference_ns(&end_time, &start_time) / (float)BENCH_ITS;
    printf(
        "AGAIB Read the first %d integers from SSD as array in %f [ns]\n",
        N_INTS,
        time_per_it_ns
    );

    free(integers_to_read);
    free(integers_to_write);

    return 0;
}
