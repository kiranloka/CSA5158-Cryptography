#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to compute ax mod q
void compute_ax(mpz_t ax, mpz_t a, mpz_t x, mpz_t q) {
    mpz_powm(ax, a, x, q);
}

int main() {
    // Public numbers
    mpz_t a, q;
    mpz_init_set_str(a, "2", 10);
    mpz_init_set_str(q, "23", 10);

    // Alice's secret number
    mpz_t alice_x;
    mpz_init_set_str(alice_x, "4", 10);

    // Bob's secret number
    mpz_t bob_x;
    mpz_init_set_str(bob_x, "3", 10);

    // Alice computes ax mod q and sends it to Bob
    mpz_t alice_ax;
    mpz_init(alice_ax);
    compute_ax(alice_ax, a, alice_x, q);

    // Bob computes ax mod q and sends it to Alice
    mpz_t bob_ax;
    mpz_init(bob_ax);
    compute_ax(bob_ax, a, bob_x, q);

    // Alice computes the shared secret key
    mpz_t alice_key;
    mpz_init(alice_key);
    compute_ax(alice_key, bob_ax, alice_x, q);

    // Bob computes the shared secret key
    mpz_t bob_key;
    mpz_init(bob_key);
    compute_ax(bob_key, alice_ax, bob_x, q);

    // Print the shared secret keys
    gmp_printf("Alice's key: %Zx\n", alice_key);
    gmp_printf("Bob's key: %Zx\n", bob_key);

    mpz_clear(a);
    mpz_clear(q);
    mpz_clear(alice_x);
    mpz_clear(bob_x);
    mpz_clear(alice_ax);
    mpz_clear(bob_ax);
    mpz_clear(alice_key);
    mpz_clear(bob_key);

    return 0;
}