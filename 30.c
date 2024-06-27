#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 16

void cbc_mac(uint8_t* key, uint8_t* message, int message_len, uint8_t* mac) {
    uint8_t iv[BLOCK_SIZE] = {0}; // initialization vector
    uint8_t cipher[BLOCK_SIZE];

    // Encrypt the message in CBC mode
    for (int i = 0; i < message_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            cipher[j] = message[i + j] ^ iv[j];
        }
        // Encrypt the block using the key (simulated using a simple XOR)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            cipher[j] ^= key[j];
        }
        // Update the IV for the next block
        memcpy(iv, cipher, BLOCK_SIZE);
    }

    // The last block is the MAC
    memcpy(mac, iv, BLOCK_SIZE);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    uint8_t message[BLOCK_SIZE] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56};
    uint8_t mac[BLOCK_SIZE];

    // Compute the CBC MAC for the one-block message X
    cbc_mac(key, message, BLOCK_SIZE, mac);
    printf("MAC for X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    // Create a two-block message X || (X ⊕ T)
    uint8_t two_block_message[2 * BLOCK_SIZE];
    memcpy(two_block_message, message, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        two_block_message[BLOCK_SIZE + i] = message[i] ^ mac[i];
    }

    // The adversary can immediately compute the CBC MAC for the two-block message
    uint8_t two_block_mac[BLOCK_SIZE];
    cbc_mac(key, two_block_message, 2 * BLOCK_SIZE, two_block_mac);
    printf("MAC for X || (X ⊕ T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", two_block_mac[i]);
    }
    printf("\n");

    return 0;
}