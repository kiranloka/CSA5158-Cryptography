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

void des_ecb_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, DES_key_schedule *ks)
{
    DES_ecb_encrypt((DES_cblock *)plaintext, (DES_cblock *)ciphertext, ks, DES_ENCRYPT);
}

void des_ecb_decrypt(const unsigned char *ciphertext, unsigned char *plaintext, DES_key_schedule *ks)
{
    DES_ecb_encrypt((DES_cblock *)ciphertext, (DES_cblock *)plaintext, ks, DES_DECRYPT);
}

int main()
{
    // Key for DES
    DES_cblock key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_key_schedule schedule;

    // Set the key
    if (DES_set_key_checked(&key, &schedule))
    {
        handleErrors();
    }

    // Plaintext
    unsigned char plaintext[] = "This is a test message to encrypt using DES ECB mode.";
    size_t plaintext_len = strlen((char *)plaintext);

    // Pad plaintext to be a multiple of BLOCK_SIZE
    size_t padded_len = ((plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    unsigned char *padded_plaintext = (unsigned char *)malloc(padded_len);
    memset(padded_plaintext, 0, padded_len);
    memcpy(padded_plaintext, plaintext, plaintext_len);

    // Buffer for ciphertext
    unsigned char *ciphertext = (unsigned char *)malloc(padded_len);
    memset(ciphertext, 0, padded_len);

    // Encrypt each block
    for (size_t i = 0; i < padded_len; i += BLOCK_SIZE)
    {
        des_ecb_encrypt(padded_plaintext + i, ciphertext + i, &schedule);
    }

    // Print the ciphertext
    printData("Ciphertext", ciphertext, padded_len);

    // Buffer for decrypted text
    unsigned char *decryptedtext = (unsigned char *)malloc(padded_len);
    memset(decryptedtext, 0, padded_len);

    // Decrypt each block
    for (size_t i = 0; i < padded_len; i += BLOCK_SIZE)
    {
        des_ecb_decrypt(ciphertext + i, decryptedtext + i, &schedule);
    }

    // Print the decrypted text
    printData("Decrypted text", decryptedtext, padded_len);

    // Free allocated memory
    free(padded_plaintext);
    free(ciphertext);
    free(decryptedtext);

    return 0;
}
