#include <stdio.h>
#include <stdlib.h>

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

void solveAffineEquations(int c1, int p1, int c2, int p2, int *a, int *b) {
    // Solve the equations: a * p1 + b ≡ c1 (mod 26) and a * p2 + b ≡ c2 (mod 26)
    // Rearrange to: a * p1 + b = c1 + 26k and a * p2 + b = c2 + 26m
    int x1 = p1, x2 = p2;
    int y1 = c1, y2 = c2;
    
    // Calculate a: (y2 - y1) ≡ a * (x2 - x1) (mod 26)
    int a_inv = modInverse(x2 - x1, 26);
    if (a_inv == -1) {
        printf("No solution found.\n");
        exit(1);
    }
    *a = ((y2 - y1) * a_inv) % 26;
    if (*a < 0) *a += 26;

    // Calculate b: y1 ≡ a * x1 + b (mod 26)
    *b = (y1 - (*a * x1) % 26 + 26) % 26;
}

int main() {
    char ciphertext[100], plaintext[100];
    int a, b;
    int c1 = 'B' - 'A'; // Index of B
    int c2 = 'U' - 'A'; // Index of U
    int p1 = 'E' - 'A'; // Index of E
    int p2 = 'T' - 'A'; // Index of T

    solveAffineEquations(c1, p1, c2, p2, &a, &b);

    printf("Determined keys: a = %d, b = %d\n", a, b);

    printf("Enter the ciphertext: ");
    scanf(" %[^\n]s", ciphertext);

    decrypt(ciphertext, a, b, plaintext);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}

