//8th problem in the word document

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherAlphabet(const char* keyword, char* cipherAlphabet) {
    int i, j, k = 0;
    int used[ALPHABET_SIZE] = {0};
    
    // Add the keyword to the cipher alphabet
    for (i = 0; keyword[i] != '\0'; i++) {
        if (!used[toupper(keyword[i]) - 'A']) {
            cipherAlphabet[k++] = toupper(keyword[i]);
            used[toupper(keyword[i]) - 'A'] = 1;
        }
    }

    // Add the remaining letters to the cipher alphabet
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            cipherAlphabet[k++] = 'A' + i;
        }
    }
}

void createMapping(const char* plainAlphabet, const char* cipherAlphabet, char* map) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        map[plainAlphabet[i] - 'A'] = cipherAlphabet[i];
    }
}

void encrypt(const char* plaintext, char* ciphertext, const char* map) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            ciphertext[i] = map[toupper(plaintext[i]) - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(const char* ciphertext, char* plaintext, const char* map) {
    char reverseMap[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        reverseMap[(int)map[i] - 'A'] = 'A' + i;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = reverseMap[toupper(ciphertext[i]) - 'A'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plainAlphabet[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipherAlphabet[ALPHABET_SIZE];
    char map[ALPHABET_SIZE];

    generateCipherAlphabet(keyword, cipherAlphabet);
    createMapping(plainAlphabet, cipherAlphabet, map);

    char plaintext[100], ciphertext[100], decryptedtext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    encrypt(plaintext, ciphertext, map);
    printf("Encrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, decryptedtext, map);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}
