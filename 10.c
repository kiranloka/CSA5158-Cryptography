//10th program 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Predefined Playfair matrix
char keySquare[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void preprocessPlaintext(const char* input, char* output) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i] == 'J' ? 'I' : input[i]);
        }
    }
    output[j] = '\0';
}

void createDigraphs(const char* plaintext, char* digraphs) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i += 2) {
        digraphs[j++] = plaintext[i];
        if (plaintext[i + 1] == '\0' || plaintext[i] == plaintext[i + 1]) {
            digraphs[j++] = 'X';
            if (plaintext[i + 1] != '\0') {
                i--;
            }
        } else {
            digraphs[j++] = plaintext[i + 1];
        }
    }
    digraphs[j] = '\0';
}

void findPosition(char keySquare[SIZE][SIZE], char c, int* row, int* col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keySquare[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptDigraph(char keySquare[SIZE][SIZE], char in1, char in2, char* out1, char* out2) {
    int row1, col1, row2, col2;
    findPosition(keySquare, in1, &row1, &col1);
    findPosition(keySquare, in2, &row2, &col2);

    if (row1 == row2) {
        *out1 = keySquare[row1][(col1 + 1) % SIZE];
        *out2 = keySquare[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *out1 = keySquare[(row1 + 1) % SIZE][col1];
        *out2 = keySquare[(row2 + 1) % SIZE][col2];
    } else {
        *out1 = keySquare[row1][col2];
        *out2 = keySquare[row2][col1];
    }
}

void encryptPlayfair(const char* plaintext, char* ciphertext, char keySquare[SIZE][SIZE]) {
    char processedText[100];
    char digraphs[100];
    int i, len;

    preprocessPlaintext(plaintext, processedText);
    createDigraphs(processedText, digraphs);
    len = strlen(digraphs);

    for (i = 0; i < len; i += 2) {
        encryptDigraph(keySquare, digraphs[i], digraphs[i + 1], &ciphertext[i], &ciphertext[i + 1]);
    }
    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];

    encryptPlayfair(plaintext, ciphertext, keySquare);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
