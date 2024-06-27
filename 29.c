#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STATE_SIZE 1600
#define CAPACITY_SIZE 1024
#define BLOCK_SIZE 1024

typedef struct {
    uint64_t lanes[25][64];
} state_t;

void init_state(state_t* state) {
    memset(state->lanes, 0, sizeof(state->lanes));
}

void absorb_block(state_t* state, uint64_t* block) {
    for (int i = 0; i < BLOCK_SIZE / 64; i++) {
        state->lanes[i / 64][i % 64] ^= block[i];
    }
}

int count_zero_lanes(state_t* state) {
    int count = 0;
    for (int i = CAPACITY_SIZE / 64; i < 25; i++) {
        for (int j = 0; j < 64; j++) {
            if (state->lanes[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    state_t state;
    init_state(&state);

    // Assume each lane in the first message block has at least one nonzero bit
    uint64_t block[BLOCK_SIZE / 64];
    for (int i = 0; i < BLOCK_SIZE / 64; i++) {
        block[i] = (uint64_t) rand() << 32 | (uint64_t) rand();
    }

    int rounds = 0;
    while (1) {
        absorb_block(&state, block);
        int zero_lanes = count_zero_lanes(&state);
        printf("Round %d: %d zero lanes remaining\n", rounds, zero_lanes);
        if (zero_lanes == 0) {
            break;
        }
        rounds++;
    }

    printf("All capacity lanes have at least one nonzero bit after %d rounds\n", rounds);

    return 0;
}