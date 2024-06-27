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

// Counter mode functions
void counter_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *counter, unsigned char *ciphertext)
{
    int num_blocks = (plaintext_len + 8 - 1) / 8;
    unsigned char block[8];

    for (int i = 0; i < num_blocks; i++)
    {
        memcpy(block, counter, 8);
        sdes_encrypt(block, key);
        for (int j = 0; j < 8; j++)
        {
            ciphertext[i * 8 + j] = plaintext[i * 8 + j] ^ block[j];
        }
        // Increment the counter
        for (int j = 7; j >= 0; j--)
        {
            if (++counter[j] == 0)
            {
                continue;
            }
            break;
        }
    }
}

void counter_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *counter, unsigned char *plaintext)
{
    int num_blocks = (ciphertext_len + 8 - 1) / 8;
    unsigned char block[8];

    for (int i = 0; i < num_blocks; i++)
    {
        memcpy(block, counter, 8);
        sdes_encrypt(block, key);
        for (int j = 0; j < 8; j++)
        {
            plaintext[i * 8 + j] = ciphertext[i * 8 + j] ^ block[j];
        }
        // Increment the counter
        for (int j = 7; j >= 0; j--)
        {
            if (++counter[j] == 0)
            {
                continue;
            }
            break;
        }
    }
}

int main()
{
    unsigned char key[] = {0x3, 0x5, 0x7, 0x9, 0xB, 0xD, 0xF, 0x11};
    unsigned char counter[] = {0x0, 0x0, 0x0, 0x0};
    unsigned char plaintext[] = {0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0};
    int plaintext_len = 16;

    unsigned char ciphertext[16];

    counter_encrypt(plaintext, plaintext_len, key, counter, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    unsigned char decrypted[16];
    counter_decrypt(ciphertext, 16, key, counter, decrypted);

    printf("Decrypted: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}