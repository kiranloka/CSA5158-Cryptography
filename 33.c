#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>

// DSA signature generation
void dsa_sign(DSA* dsa, unsigned char* message, int message_len, unsigned char* signature) {
    BIGNUM* k = BN_new();
    BN_rand(k, 160, 0, 0); // generate a random k value
    DSA_sign(0, message, message_len, signature, k, dsa);
    BN_free(k);
}

// RSA signature generation
void rsa_sign(RSA* rsa, unsigned char* message, int message_len, unsigned char* signature) {
    RSA_sign(NID_sha1, message, message_len, signature, rsa);
}

int main() {
    // DSA key generation
    DSA* dsa = DSA_new();
    DSA_generate_parameters_ex(dsa, 1024, 160, NULL);
    DSA_generate_key(dsa);

    // RSA key generation
    RSA* rsa = RSA_new();
    RSA_generate_key_ex(rsa, 1024, 65537, NULL);

    // Message to sign
    unsigned char message[] = "Hello, World!";
    int message_len = strlen(message);

    // DSA signature generation
    unsigned char dsa_signature1[40];
    dsa_sign(dsa, message, message_len, dsa_signature1);

    unsigned char dsa_signature2[40];
    dsa_sign(dsa, message, message_len, dsa_signature2);

    // RSA signature generation
    unsigned char rsa_signature[128];
    rsa_sign(rsa, message, message_len, rsa_signature);

    // Print signatures
    printf("DSA Signature 1: ");
    for (int i = 0; i < 40; i++) {
        printf("%02x", dsa_signature1[i]);
    }
    printf("\n");

    printf("DSA Signature 2: ");
    for (int i = 0; i < 40; i++) {
        printf("%02x", dsa_signature2[i]);
    }
    printf("\n");

    printf("RSA Signature: ");
    for (int i = 0; i < 128; i++) {
        printf("%02x", rsa_signature[i]);
    }
    printf("\n");

    // Clean up
    DSA_free(dsa);
    RSA_free(rsa);

    return 0;
}