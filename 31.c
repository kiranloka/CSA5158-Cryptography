#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128

#define CONSTANT_64 0x000000000000008B
#define CONSTANT_128 0x000000000000000000000000008D

void generate_subkeys(uint8_t* key, int block_size, uint8_t* subkey1, uint8_t* subkey2) {
    uint8_t zero_block[BLOCK_SIZE_128 / 8] = {0}; // block of zeros
    uint8_t encrypted_block[BLOCK_SIZE_128 / 8];

    // Encrypt the block of zeros using the key (simulated using a simple XOR)
    for (int i = 0; i < block_size / 8; i++) {
        encrypted_block[i] = zero_block[i] ^ key[i];
    }

    // Derive the first subkey
    for (int i = 0; i < block_size / 8; i++) {
        subkey1[i] = encrypted_block[i] << 1;
    }
    if (block_size == BLOCK_SIZE_64) {
        for (int i = 0; i < BLOCK_SIZE_64 / 8; i++) {
            subkey1[i] ^= ((uint8_t*) &CONSTANT_64)[i];
        }
    } else if (block_size == BLOCK_SIZE_128) {
        for (int i = 0; i < BLOCK_SIZE_128 / 8; i++) {
            subkey1[i] ^= ((uint8_t*) &CONSTANT_128)[i];
        }
    }

    // Derive the second subkey
    for (int i = 0; i < block_size / 8; i++) {
        subkey2[i] = subkey1[i] << 1;
    }
    if (block_size == BLOCK_SIZE_64) {
        for (int i = 0; i < BLOCK_SIZE_64 / 8; i++) {
            subkey2[i] ^= ((uint8_t*) &CONSTANT_64)[i];
        }
    } else if (block_size == BLOCK_SIZE_128) {
        for (int i = 0; i < BLOCK_SIZE_128 / 8; i++) {
            subkey2[i] ^= ((uint8_t*) &CONSTANT_128)[i];
        }
    }
}

int main() {
    uint8_t key[BLOCK_SIZE_128 / 8] = {0x01, 0x02, 0x03, 0x04,