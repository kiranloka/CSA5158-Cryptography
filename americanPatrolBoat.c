//This is the 9th program in the word document

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeySquare(char key[], char keySquare[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;
    char c;

    // Mark 'J' as used since it is typically combined with 'I' in the Playfair cipher
    used['J' - 'A'] = 1;

    // Fill the key square with the keyword
    for (i = 0; key[i] != '\0'; i++) {
        c = toupper(key[i]);
        if (!used[c - 'A']) {
            keySquare[k / SIZE][k % SIZE] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }

    // Fill the rest of the key square with remaining letters
    for (c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            keySquare[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
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

void decryptDigraph(char keySquare[SIZE][SIZE], char in1, char in2, char* out1, char* out2) {
    int row1, col1, row2, col2;
    findPosition(keySquare, in1, &row1, &col1);
    findPosition(keySquare, in2, &row2, &col2);

    if (row1 == row2) {
        *out1 = keySquare[row1][(col1 + SIZE - 1) % SIZE];
        *out2 = keySquare[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        *out1 = keySquare[(row1 + SIZE - 1) % SIZE][col1];
        *out2 = keySquare[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        *out1 = keySquare[row1][col2];
        *out2 = keySquare[row2][col1];
    }
}

void decryptPlayfair(char ciphertext[], char plaintext[], char keySquare[SIZE][SIZE]) {
    int i, len = strlen(ciphertext);
    char in1, in2, out1, out2;

    for (i = 0; i < len; i += 2) {
        in1 = toupper(ciphertext[i]);
        in2 = toupper(ciphertext[i + 1]);
        decryptDigraph(keySquare, in1, in2, &out1, &out2);
        plaintext[i] = out1;
        plaintext[i + 1] = out2;
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "PLAYFAIR";  // Example keyword
    char keySquare[SIZE][SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[sizeof(ciphertext)];

    generateKeySquare(key, keySquare);

    printf("Key Square:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keySquare[i][j]);
        }
        printf("\n");
    }

    decryptPlayfair(ciphertext, plaintext, keySquare);

    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}
