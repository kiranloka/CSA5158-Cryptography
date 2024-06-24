#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int alpha[26] = {0};
    int i, j, k = 0, l = 0;
    
    // Fill the key matrix with the keyword
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'j') {
            key[i] = tolower(key[i]);
            if (!alpha[key[i] - 'a']) {
                keyMatrix[k][l++] = key[i];
                alpha[key[i] - 'a'] = 1;
                if (l == SIZE) {
                    l = 0;
                    k++;
                }
            }
        }
    }

    // Fill the remaining matrix with other letters
    for (i = 0; i < 26; i++) {
        if (i + 'a' != 'j' && !alpha[i]) {
            keyMatrix[k][l++] = i + 'a';
            if (l == SIZE) {
                l = 0;
                k++;
            }
        }
    }
}

void prepareText(char text[], char preparedText[]) {
    int i, j = 0;
    int len = strlen(text);

    for (i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            preparedText[j++] = tolower(text[i]);
        }
    }
    preparedText[j] = '\0';

    for (i = 0; i < j; i += 2) {
        if (i + 1 == j || preparedText[i] == preparedText[i + 1]) {
            for (int k = j; k > i + 1; k--) {
                preparedText[k] = preparedText[k - 1];
            }
            preparedText[i + 1] = (preparedText[i] == 'x') ? 'q' : 'x';
            j++;
        }
    }

    if (j % 2 != 0) {
        preparedText[j++] = 'x';
    }
    preparedText[j] = '\0';
}

void findPosition(char keyMatrix[SIZE][SIZE], char c, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char keyMatrix[SIZE][SIZE], char a, char b, char *encryptedPair) {
    int row1, col1, row2, col2;

    findPosition(keyMatrix, a, &row1, &col1);
    findPosition(keyMatrix, b, &row2, &col2);

    if (row1 == row2) {
        encryptedPair[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        encryptedPair[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encryptedPair[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        encryptedPair[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        encryptedPair[0] = keyMatrix[row1][col2];
        encryptedPair[1] = keyMatrix[row2][col1];
    }
}

void encrypt(char key[], char plaintext[], char ciphertext[]) {
    char keyMatrix[SIZE][SIZE];
    char preparedText[100];
    int i;

    generateKeyMatrix(key, keyMatrix);
    prepareText(plaintext, preparedText);

    for (i = 0; i < strlen(preparedText); i += 2) {
        encryptPair(keyMatrix, preparedText[i], preparedText[i + 1], &ciphertext[i]);
    }
    ciphertext[i] = '\0';
}

int main() {
    char key[100], plaintext[100], ciphertext[100];

    printf("Enter keyword: ");
    scanf("%s", key);
    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    encrypt(key, plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
