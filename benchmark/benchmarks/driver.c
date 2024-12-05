#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


#define GB ((uint64_t)(1024 * 1024 * 1024))
#define MAX_SIZE (64 * GB)


uint64_t run(uint64_t times, uint64_t size, void *source, void *target);


// try to parse a number with at most 19 digits, returns if successful
bool try_parse(char *s, uint64_t *v) {
    int l = 0;
    while (s[l]) {
        if (!isdigit(s[l])) {
            return false;
        }
        l++;
    }

    if (l == 0 || l > 19) {
        return false;
    }

    char *endptr;
    *v = strtoull(s, &endptr, 10);
    return *endptr == '\0';
}

uint64_t min(uint64_t x, uint64_t y) {
    return x < y ? x : y;
}

int main(int argc, char *argv[]) {
    // parse arguments
    uint64_t times, size;
    if (argc != 3 || !try_parse(argv[1], &times) || !try_parse(argv[2], &size) || (size & 31) || size > MAX_SIZE) {
        printf("Usage: %s <times> <size>\n  times: number of times to run the benchmark\n  size: size of the blocks of memory to allocate (in bytes) -- needs to be a multiple of 32 and less than 64 GiB\n", argv[0]);
        return 1;
    }

    // allocate memory
    void *source = aligned_alloc(min(4096, size), size);
	void *target = aligned_alloc(min(4096, size), size);

    if (!source || !target) {
        printf("Failed to allocate memory. Please use a lower value for size or free some memory, and try again.");
        return 1;
    }

    // measure how long the external 'run' method takes
    struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
    run(times, size, source, target);
	clock_gettime(CLOCK_MONOTONIC, &end);

    // calculate and print throughput
	double gigabytes = 1.0 * size * times / 1024.0 / 1024.0 / 1024.0;
	double seconds = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("%f\n", gigabytes / seconds);

    // free and exit
	free(source);
	free(target);
    return 0;
}
