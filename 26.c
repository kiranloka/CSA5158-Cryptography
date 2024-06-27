#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to generate a random prime number
void generate_prime(mpz_t p)
{
    mpz_urandomb(p, 256); // Generate a random 256-bit number
    mpz_nextprime(p, p);  // Make it prime
}

// Function to generate a public and private key pair
void generate_keypair(mpz_t p, mpz_t q, mpz_t n, mpz_t e, mpz_t d)
{
    // Generate two random prime numbers p and q
    generate_prime(p);
    generate_prime(q);

    // Calculate n = p * q
    mpz_mul(n, p, q);

    // Calculate Euler's totient function phi(n) = (p-1) * (q-1)
    mpz_t phi;
    mpz_init(phi);
    mpz_sub_ui(phi, p, 1);
    mpz_mul(phi, phi, q);
    mpz_sub_ui(phi, phi, 1);

    // Choose a public exponent e such that 1 < e < phi and gcd(e, phi) = 1
    mpz_set_ui(e, 65537); // A common choice for e

    // Calculate the private exponent d such that d * e = 1 mod phi
    mpz_invert(d, e, phi);

    mpz_clear(phi);
}

// Function to encrypt a message using the public key
void encrypt(mpz_t ciphertext, mpz_t message, mpz_t e, mpz_t n)
{
    mpz_powm(ciphertext, message, e, n);
}

// Function to decrypt a ciphertext using the private key
void decrypt(mpz_t plaintext, mpz_t ciphertext, mpz_t d, mpz_t n)
{
    mpz_powm(plaintext, ciphertext, d, n);
}

int main()
{
    // Initialize GMP library
    mpz_init_set_ui(p, 0);
    mpz_init_set_ui(q, 0);
    mpz_init_set_ui(n, 0);
    mpz_init_set_ui(e, 0);
    mpz_init_set_ui(d, 0);
    mpz_init_set_ui(message, 0);
    mpz_init_set_ui(ciphertext, 0);
    mpz_init_set_ui(plaintext, 0);

    // Generate a key pair for Bob
    generate_keypair(p, q, n, e, d);

    // Print Bob's public key (e, n)
    printf("Bob's public key: (e, n) = (%zu, %zu)\n", mpz_get_ui(e), mpz_get_ui(n));

    // Suppose Bob leaks his private key d
    printf("Bob's private key: d = %zu\n", mpz_get_ui(d));

    // Bob generates a new public and private key pair without changing the modulus n
    mpz_t new_e, new_d;
    mpz_init_set_ui(new_e, 0);
    mpz_init_set_ui(new_d, 0);
    generate_keypair(p, q, n, new_e, new_d);

    // Print Bob's new public key (new_e, n)
    printf("Bob's new public key: (new_e, n) = (%zu, %zu)\n", mpz_get_ui(new_e), mpz_get_ui(n));

    // Is this safe? No, because an attacker can still use the leaked private key d to decrypt messages
    // encrypted with the new public key (new_e, n)

    // Example: encrypt a message using the new public key
    mpz_set_ui(message, 123); // Example message
    mpz_t new_ciphertext;
    mpz_init_set_ui(new_ciphertext, 0);
    encrypt(new_ciphertext, message, new_e, n);

    // An attacker can decrypt the ciphertext using the leaked private key d
    mpz_t attacker_plaintext;
    mpz_init_set_ui(attacker_plaintext, 0);
    decrypt(attacker_plaintext, new_ciphertext, d, n);

    printf("Attacker decrypted message: %zu\n", mpz_get_ui(attacker_plaintext));

    // Clean up
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(message);
    mpz_clear(ciphertext);
    mpz_clear(plaintext);
    mpz_clear(new_e);
    mpz_clear(new_d);
    mpz_clear(new_ciphertext);
    mpz_clear(attacker_plaintext);

    return 0;
}