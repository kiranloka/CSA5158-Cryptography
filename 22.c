#include <stdio.h>
#include <string.h>

// S-DES functions
void sdes_encrypt(unsigned char *block, unsigned char *key)
{
    // S-DES encryption function
    // Not implemented here, but you can find the implementation online
}

void sdes_decrypt(unsigned char *block, unsigned char *key)
{
    // S-DES decryption function
    // Not implemented here, but you can find the implementation online
}

// CBC mode functions
void cbc_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    int num_blocks = (plaintext_len + 8 - 1) / 8;
    unsigned char block[8];

    for (int i = 0; i < num_blocks; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            block[j] = plaintext[i * 8 + j] ^ iv[j];
        }
        sdes_encrypt(block, key);
        for (int j = 0; j < 8; j++)
        {
            ciphertext[i * 8 + j] = block[j];
        }
        memcpy(iv, block, 8);
    }
}

void cbc_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)
{
    int num_blocks = (ciphertext_len + 8 - 1) / 8;
    unsigned char block[8];

    for (int i = 0; i < num_blocks; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            block[j] = ciphertext[i * 8 + j];
        }
        sdes_decrypt(block, key);
        for (int j = 0; j < 8; j++)
        {
            plaintext[i * 8 + j] = block[j] ^ iv[j];
        }
        memcpy(iv, ciphertext + i * 8, 8);
    }
}

int main()
{
    unsigned char key[] = {0x3, 0x5, 0x7, 0x9, 0xB, 0xD, 0xF, 0x11};
    unsigned char iv[] = {0xA, 0xA};
    unsigned char plaintext[] = {0x0, 0x0, 0x0, 0x1, 0x0, 0x10, 0x0, 0x11};
    int plaintext_len = 8;

    unsigned char ciphertext[8];

    cbc_encrypt(plaintext, plaintext_len, key, iv, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    unsigned char decrypted[8];
    cbc_decrypt(ciphertext, 8, key, iv, decrypted);

    printf("Decrypted: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%02x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}