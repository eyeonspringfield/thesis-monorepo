// Sums an array but bails if a sentinel is hit. Sentinel is planted pseudorandomly.

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024
#define SENTINEL_VALUE 0xDEADBAD4U

static void seed_rng() {
    uint32_t seed = (uint32_t)time(NULL);
    srand(seed);
}

static size_t prepare_inputs(uint32_t *buffer, size_t len) {
    size_t sentinel_index = (size_t)(rand() % len);
    for (size_t i = 0; i < len; ++i) {
        buffer[i] = (i == sentinel_index) ? SENTINEL_VALUE : (uint32_t)rand();
    }
    return sentinel_index;
}

static int guarded_sum(const uint32_t *buffer,
                       size_t len,
                       uint32_t sentinel,
                       uint64_t *out_sum,
                       size_t *sentinel_index) {
    uint64_t sum = 0;
    for (size_t i = 0; i < len; ++i) {
        if (buffer[i] == sentinel) {
            *sentinel_index = i;
            *out_sum = sum;
            return -1;
        }
        sum += buffer[i];
    }
    *sentinel_index = SIZE_MAX;
    *out_sum = sum;
    return 0;
}

int main() {
    uint32_t data[ARRAY_SIZE];
    seed_rng();

    size_t planted = prepare_inputs(data, ARRAY_SIZE);
    size_t seen = SIZE_MAX;
    uint64_t sum = 0;

    int rc = guarded_sum(data, ARRAY_SIZE, SENTINEL_VALUE, &sum, &seen);

    if (rc == 0) {
        printf("No sentinel encountered. sum=%" PRIu64 " processed=%d\n", sum, ARRAY_SIZE);
    } else {
        printf("Sentinel hit at index=%zu (planted=%zu) partial_sum=%" PRIu64 "\n",
               seen, planted, sum);
    }

    return rc == 0 ? 0 : 1;
}