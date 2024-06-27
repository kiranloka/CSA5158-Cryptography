#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to encrypt a message using RSA
void encrypt(mpz_t ciphertext, mpz_t plaintext, mpz_t e, mpz_t n) {
    mpz_powm(ciphertext, plaintext, e, n);
}

// Function to decrypt a ciphertext using RSA
void decrypt(mpz_t plaintext, mpz_t ciphertext, mpz_t d, mpz_t n) {
    mpz_powm(plaintext, ciphertext, d, n);
}

int main() {
    // Large modulus n (public key)
    mpz_t n;
    mpz_init_set_str(n, "12345678901234567890", 10);

    // Public exponent e (public key)
    mpz_t e;
    mpz_init_set_str(e, "65537", 10);

    // Private exponent d (private key)
    mpz_t d;
    mpz_init(d);

    // Compute d such that d*e = 1 (mod (n-1))
    mpz_t phi_n;
    mpz_init(phi_n);
    mpz_sub_ui(phi_n, n, 1);
    mpz_gcdext(d, NULL, NULL, e, phi_n);

    // Message to encrypt
    char message[] = "HELLO";

    // Encrypt each character separately
    for (int i = 0; i < strlen(message); i++) {
        mpz_t plaintext, ciphertext;
        mpz_init(plaintext);
        mpz_init(ciphertext);

        // Convert character to integer (A=0, B=1, ..., Z=25)
        mpz_set_ui(plaintext, message[i] - 'A');

        // Encrypt
        encrypt(ciphertext, plaintext, e, n);

        // Print ciphertext
        gmp_printf("Ciphertext for %c: %Zx\n", message[i], ciphertext);

        mpz_clear(plaintext);
        mpz_clear(ciphertext);
    }

    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(phi_n);

    return 0;
}