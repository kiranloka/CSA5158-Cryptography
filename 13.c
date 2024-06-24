#include <stdio.h>

#define MATRIX_SIZE 2
#define MODULO 26

// Function to calculate modular inverse of a matrix mod 26 (only for 2x2 matrices)
void matrixInverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + MODULO) % MODULO;
    int detInv = 0;

    // Find modular multiplicative inverse of determinant
    for (int i = 1; i < MODULO; i++) {
        if ((det * i) % MODULO == 1) {
            detInv = i;
            break;
        }
    }

    // Calculate inverse matrix elements
    inverse[0][0] = (key[1][1] * detInv) % MODULO;
    inverse[1][1] = (key[0][0] * detInv) % MODULO;
    inverse[0][1] = (-key[0][1] * detInv + MODULO) % MODULO;
    inverse[1][0] = (-key[1][0] * detInv + MODULO) % MODULO;
}

// Function to solve the Hill cipher using known plaintext attack
void hillKnownPlaintextAttack(int plaintext_num[][MATRIX_SIZE], int ciphertext_num[][MATRIX_SIZE], int num_pairs, int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE];

    // Calculate inverse of key matrix
    matrixInverse(key, inverseKey);

    // Print the key matrix and its inverse for verification
    printf("Original Key Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n\n", key[1][0], key[1][1]);

    printf("Inverse Key Matrix:\n");
    printf("%d %d\n", inverseKey[0][0], inverseKey[0][1]);
    printf("%d %d\n\n", inverseKey[1][0], inverseKey[1][1]);

    // Calculate deduced key matrix using the plaintext-ciphertext pairs
    for (int i = 0; i < num_pairs; i++) {
        int deduced_key[MATRIX_SIZE][MATRIX_SIZE];
        int plaintext[MATRIX_SIZE] = { plaintext_num[i][0], plaintext_num[i][1] };
        int ciphertext[MATRIX_SIZE] = { ciphertext_num[i][0], ciphertext_num[i][1] };

        // Solve the equation: C = K * P
        for (int row = 0; row < MATRIX_SIZE; row++) {
            for (int col = 0; col < MATRIX_SIZE; col++) {
                deduced_key[row][col] = 0;
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    deduced_key[row][col] += ciphertext[k] * inverseKey[k][col];
                }
                deduced_key[row][col] %= MODULO;
            }
        }

        // Print deduced key matrix
        printf("Deduced Key Matrix from Pair %d:\n", i + 1);
        printf("%d %d\n", deduced_key[0][0], deduced_key[0][1]);
        printf("%d %d\n\n", deduced_key[1][0], deduced_key[1][1]);
    }
}

int main() {
    // Given plaintext-ciphertext pairs (assuming known numbers)
    int plaintext_num[3][MATRIX_SIZE] = {
        {12, 4},    // "ME"
        {4, 19},    // "ET"
        {12, 4}     // "ME"
    };
    int ciphertext_num[3][MATRIX_SIZE] = {
        {5, 10},    // "FH"
        {24, 14},   // "YG"
        {5, 10}     // "FH"
    };

    // Key matrix to be deduced
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };

    // Perform known plaintext attack to deduce the key matrix
    hillKnownPlaintextAttack(plaintext_num, ciphertext_num, 3, key);

    return 0;
}
