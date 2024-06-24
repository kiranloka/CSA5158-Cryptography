#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MODULO 26

// Function to convert character to corresponding number (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Function to convert number to corresponding character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Function to perform matrix multiplication of 2x2 matrices mod 26
void matrixMultiply(int key[MATRIX_SIZE][MATRIX_SIZE], int input[MATRIX_SIZE], int output[MATRIX_SIZE]) {
    output[0] = (key[0][0] * input[0] + key[0][1] * input[1]) % MODULO;
    output[1] = (key[1][0] * input[0] + key[1][1] * input[1]) % MODULO;
}

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

// Function to encrypt plaintext using Hill cipher
void hillEncrypt(const char plaintext[], const int key[MATRIX_SIZE][MATRIX_SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    int pairs = len / 2 + (len % 2); // Number of digraph pairs
    int plaintextNum[MATRIX_SIZE], ciphertextNum[MATRIX_SIZE];
    int k = 0;

    for (int i = 0; i < pairs; i++) {
        // Convert digraph to numbers
        plaintextNum[0] = charToNum(plaintext[k++]);
        plaintextNum[1] = (k < len) ? charToNum(plaintext[k++]) : 0; // 'X' padding if odd length

        // Multiply key matrix with plaintext numbers
        matrixMultiply(key, plaintextNum, ciphertextNum);

        // Convert numbers to ciphertext characters
        ciphertext[i * 2] = numToChar(ciphertextNum[0]);
        ciphertext[i * 2 + 1] = numToChar(ciphertextNum[1]);
    }
    ciphertext[len] = '\0';
}

// Function to decrypt ciphertext using Hill cipher
void hillDecrypt(const char ciphertext[], const int key[MATRIX_SIZE][MATRIX_SIZE], char plaintext[]) {
    int len = strlen(ciphertext);
    int pairs = len / 2;
    int ciphertextNum[MATRIX_SIZE], plaintextNum[MATRIX_SIZE];
    int inverse[MATRIX_SIZE][MATRIX_SIZE];

    // Calculate inverse of key matrix
    matrixInverse(key, inverse);

    int k = 0;
    for (int i = 0; i < pairs; i++) {
        // Convert digraph to numbers
        ciphertextNum[0] = charToNum(ciphertext[k++]);
        ciphertextNum[1] = charToNum(ciphertext[k++]);

        // Multiply inverse key matrix with ciphertext numbers
        matrixMultiply(inverse, ciphertextNum, plaintextNum);

        // Convert numbers to plaintext characters
        plaintext[i * 2] = numToChar(plaintextNum[0]);
        plaintext[i * 2 + 1] = numToChar(plaintextNum[1]);
    }
    plaintext[len] = '\0';
}

int main() {
    // Key matrix
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };

    // Plaintext
    const char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    char ciphertext[100] = {'\0'};
    char decryptedPlaintext[100] = {'\0'};

    // Encrypt plaintext
    hillEncrypt(plaintext, key, ciphertext);

    // Decrypt ciphertext
    hillDecrypt(ciphertext, key, decryptedPlaintext);

    // Output results
    printf("Original Plaintext: %s\n", plaintext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);
    printf("Decrypted Plaintext: %s\n", decryptedPlaintext);

    return 0;
}
