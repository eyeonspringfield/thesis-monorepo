// Fills an array with function pointers and calls them via an index determined with a linear congruential generator.

#include <stdint.h>
#include <stdio.h>

#define INPUT_COUNT 256
#define DISPATCH_COUNT 1000

typedef int (*op_fn)(int, int);

static int op_add(int a, int b) { return a + b; }
static int op_sub(int a, int b) { return a - b; }
static int op_mul(int a, int b) { return a * b; }
static int op_xor(int a, int b) { return a ^ b; }
static int op_clamp(int a, int b) {
    int lo = b - 50;
    int hi = b + 50;
    if (a < lo) return lo;
    if (a > hi) return hi;
    return a;
}
static int op_mix(int a, int b) {
    return ((a & 0xF0F0F0F0) >> 4) | ((b & 0x0F0F0F0F) << 4);
}

static uint32_t lcg_next(uint32_t *state) {
    *state = *state * 1664525u + 1013904223u;
    return *state;
}

int main() {
    static int inputs_a[INPUT_COUNT];
    static int inputs_b[INPUT_COUNT];
    for (int i = 0; i < INPUT_COUNT; i++) {
        inputs_a[i] = (i * 7) - 100;
        inputs_b[i] = (i * 13) + 50;
    }

    op_fn table[] = { op_add, op_sub, op_mul, op_xor, op_clamp, op_mix };
    const int table_size = sizeof(table) / sizeof(table[0]);
    uint32_t rng = 0x0D15EA5Eu;
    int acc = 0;

    for (int i = 0; i < DISPATCH_COUNT; i++) {
        uint32_t r = lcg_next(&rng);
        int index = r % INPUT_COUNT;
        int op_index = (r >> 8) % table_size;
        acc += table[op_index](inputs_a[index], inputs_b[index]);
    }

    int checksum = 0;
    for (int i = 0; i < INPUT_COUNT; i++) {
        checksum += inputs_a[i] ^ inputs_b[i];
    }

    printf("dispatcher acc: %d checksum: 0x%08X\n", acc, checksum); // print to prevent optimization out
    return 0;
}