// DES for the first 24 bits of the subkey

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 64
#define SUBKEY_SIZE 48
#define HALF_KEY_SIZE 28

// Permutation Choice 1 table (PC1)
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

// Permutation Choice 2 table (PC2)
int pc2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32};

// Number of left shifts per round
int leftShifts[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1};

// Function to perform permutation
void permute(int *input, int *output, int *table, int size)
{
    for (int i = 0; i < size; i++)
    {
        output[i] = input[table[i] - 1];
    }
}

// Function to shift left
void shiftLeft(int *input, int shift)
{
    int temp[HALF_KEY_SIZE];
    for (int i = 0; i < HALF_KEY_SIZE; i++)
    {
        temp[i] = input[i];
    }
    for (int i = 0; i < HALF_KEY_SIZE; i++)
    {
        input[i] = temp[(i + shift) % HALF_KEY_SIZE];
    }
}

// Function to generate subkeys
void generateSubkeys(int *key, int subkeys[16][SUBKEY_SIZE])
{
    int permutedKey[56];
    permute(key, permutedKey, pc1, 56);

    int left[HALF_KEY_SIZE], right[HALF_KEY_SIZE];
    for (int i = 0; i < HALF_KEY_SIZE; i++)
    {
        left[i] = permutedKey[i];
        right[i] = permutedKey[i + HALF_KEY_SIZE];
    }

    for (int round = 0; round < 16; round++)
    {
        shiftLeft(left, leftShifts[round]);
        shiftLeft(right, leftShifts[round]);

        int combined[56];
        for (int i = 0; i < HALF_KEY_SIZE; i++)
        {
            combined[i] = left[i];
            combined[i + HALF_KEY_SIZE] = right[i];
        }

        permute(combined, subkeys[round], pc2, SUBKEY_SIZE);
    }
}

int main()
{
    // Sample 64-bit key (8 bytes)
    int key[KEY_SIZE] = {
        0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
        1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1,
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
        0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1};

    int subkeys[16][SUBKEY_SIZE];
    generateSubkeys(key, subkeys);

    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++)
    {
        printf("K%d: ", i + 1);
        for (int j = 0; j < SUBKEY_SIZE; j++)
        {
            printf("%d", subkeys[i][j]);
        }
        printf("\n");
    }

    return 0;
}
