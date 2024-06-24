// Cipher block chaining

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8

void handleErrors(void)
{
    printf("An error occurred\n");
    exit(1);
}

void printData(const char *title, const void *data, int len)
{
    printf("%s : ", title);
    const unsigned char *p = (const unsigned char *)data;
    int i;
    for (i = 0; i < len; ++i)
        printf("%02X ", *p++);
    printf("\n");
}

int main()
{
    // Key and IV (Initialization Vector)
    DES_cblock key1 = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_cblock key2 = {0x98, 0x76, 0x54, 0x32, 0x10, 0xFE, 0xDC, 0xBA};
    DES_cblock key3 = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    DES_cblock iv = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0xA7, 0xB8};

    // Set the keys
    DES_key_schedule ks1, ks2, ks3;
    DES_set_key((C_Block *)key1, &ks1);
    DES_set_key((C_Block *)key2, &ks2);
    DES_set_key((C_Block *)key3, &ks3);

    // Plaintext
    unsigned char plaintext[] = "This is a test message to encrypt using 3DES CBC mode.";
    size_t plaintext_len = strlen((char *)plaintext);

    // Pad plaintext to be a multiple of BLOCK_SIZE
    size_t padded_len = ((plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    unsigned char *padded_plaintext = (unsigned char *)malloc(padded_len);
    memset(padded_plaintext, 0, padded_len);
    memcpy(padded_plaintext, plaintext, plaintext_len);

    // Buffer for ciphertext
    unsigned char *ciphertext = (unsigned char *)malloc(padded_len);
    memset(ciphertext, 0, padded_len);

    // Perform 3DES CBC encryption
    DES_ede3_cbc_encrypt(padded_plaintext, ciphertext, padded_len, &ks1, &ks2, &ks3, &iv, DES_ENCRYPT);

    // Print the ciphertext
    printData("Ciphertext", ciphertext, padded_len);

    // Reset IV for decryption
    DES_cblock iv_dec = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0xA7, 0xB8};

    // Buffer for decrypted text
    unsigned char *decryptedtext = (unsigned char *)malloc(padded_len);
    memset(decryptedtext, 0, padded_len);

    // Perform 3DES CBC decryption
    DES_ede3_cbc_encrypt(ciphertext, decryptedtext, padded_len, &ks1, &ks2, &ks3, &iv_dec, DES_DECRYPT);

    // Print the decrypted text
    printData("Decrypted text", decryptedtext, padded_len);

    // Free allocated memory
    free(padded_plaintext);
    free(ciphertext);
    free(decryptedtext);

    return 0;
}
