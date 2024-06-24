#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to find the modular multiplicative inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt the plaintext using affine cipher
void encrypt(char plaintext[], int a, int b, char ciphertext[]) {
    int i, p, c;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            p = toupper(plaintext[i]) - 'A';
            c = (a * p + b) % 26;
            ciphertext[i] = c + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

// Function to decrypt the ciphertext using affine cipher
void decrypt(char ciphertext[], int a, int b, char plaintext[]) {
    int i, c, p;
    int a_inv = modInverse(a, 26); // Find modular multiplicative inverse of 'a'
    if (a_inv == -1) {
        printf("Decryption is not possible because a and 26 are not coprime.\n");
        exit(1);
    }
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            c = toupper(ciphertext[i]) - 'A';
            p = (a_inv * (c - b + 26)) % 26; // Add 26 to handle negative values
            plaintext[i] = p + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int a, b;

    printf("Enter the values of a and b (a should be coprime with 26): ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1) {
        printf("Error: The value of 'a' must be coprime with 26.\n");
        return 1;
    }

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    encrypt(plaintext, a, b, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, a, b, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}
