// Converts an array of integers to doubles, clamps between bounds, and converts back to integers.

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1024

static void seed_rng() {
    uint32_t seed = (uint32_t)time(NULL);
    srand(seed);
}

static void fill_inputs(int32_t *in, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        uint32_t hi = (uint32_t)(rand() & 0xFFFFu);
        uint32_t lo = (uint32_t)(rand() & 0xFFFFu);
        uint32_t v = (hi << 16) | lo;
        in[i] = (int32_t)v;
    }
}

static void promote_and_clamp(const int32_t *in,
                              int32_t *out,
                              size_t len,
                              double lo,
                              double hi,
                              int64_t *checksum) {
    int64_t acc = 0;
    for (size_t i = 0; i < len; ++i) {
        double v = (double)in[i];

        if (v < lo)
            v = lo;
        else if (v > hi)
            v = hi;

        int32_t iv = (int32_t)v;
        out[i] = iv;
        acc += iv;
    }
    *checksum = acc;
}

int main() {
    int32_t in[ARRAY_SIZE];
    int32_t out[ARRAY_SIZE];

    double lo = -100000.0;
    double hi =  100000.0;

    seed_rng();
    fill_inputs(in, ARRAY_SIZE);

    int64_t checksum = 0;
    promote_and_clamp(in, out, ARRAY_SIZE, lo, hi, &checksum);

    printf("promote: len=%d checksum=%" PRId64 " lo=%g hi=%g\n",
           ARRAY_SIZE, checksum, lo, hi);

    return 0;
}
