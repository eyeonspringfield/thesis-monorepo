// Allocates and initializes a few kilobytes of memory and walks through it while loading, mixing and storing values.

#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 8192

static uint8_t bytes[MEM_SIZE];

static void init_memory() {
    for (size_t i = 0; i < MEM_SIZE; i++) {
        bytes[i] = (uint8_t)(i * 37u) ^ (i >> 2);
    }
}

int main(){
    init_memory();

    uint32_t checksum = 0;
    uint32_t acc = 0;

    for (int i = 0; i < MEM_SIZE; i += 3) {
        uint8_t b = bytes[i];
        acc ^= (uint8_t)(b ^ (acc & 0x3F)); // load and mix
        bytes[i] = (uint8_t)(b ^ (acc & 0xF)); // store modified value
        checksum += acc;
        if (b == 0xAA) {
            checksum ^= acc;
            break;
        }
    }

    for (int j = MEM_SIZE - 1; j >= 0; --j) {
        uint8_t b = bytes[j];
        acc = (acc >> 3) | (acc << 29);
        acc += (uint8_t)(b + (acc & 0x1F)); // load and mix
        bytes[j] = (uint8_t)(b + (acc & 0x0F)); // store modified value
        checksum ^= acc;
        if (b == 0x55) {
            checksum += acc;
            break;
        }
    }

    printf("memwalk checksum: 0x%08X acc: 0x%08X\n", checksum, acc); // print to prevent optimization out
    return 0;
}