#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toUpperCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void generateKey(char plaintext[], char key[], char newKey[]) {
    int lenPT = strlen(plaintext);
    int lenK = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < lenPT; i++, j++) {
        if (j == lenK) {
            j = 0;
        }
        newKey[i] = key[j];
    }
    newKey[i] = '\0';
}

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        char shift = key[i] - 'A';
        if (isupper(plaintext[i])) {
            ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
        } else if (islower(plaintext[i])) {
            ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        char shift = key[i] - 'A';
        if (isupper(ciphertext[i])) {
            plaintext[i] = ((ciphertext[i] - 'A' - shift + 26) % 26) + 'A';
        } else if (islower(ciphertext[i])) {
            plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[100], key[100], newKey[100], ciphertext[100], decryptedText[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    toUpperCase(plaintext);
    toUpperCase(key);

    generateKey(plaintext, key, newKey);
    
    encrypt(plaintext, newKey, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, newKey, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
