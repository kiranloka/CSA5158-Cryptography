#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16 // 128 bits

void ecb_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *ciphertext)
{
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++)
    {
        AES_encrypt(plaintext + i * BLOCK_SIZE, ciphertext + i * BLOCK_SIZE, &aes_key);
    }
}

void ecb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *plaintext)
{
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    int num_blocks = (ciphertext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++)
    {
        AES_decrypt(ciphertext + i * BLOCK_SIZE, plaintext + i * BLOCK_SIZE, &aes_key);
    }
}

void cbc_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned char block[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++)
    {
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
            block[j] = plaintext[i * BLOCK_SIZE + j] ^ iv[j];
        }
        AES_encrypt(block, ciphertext + i * BLOCK_SIZE, &aes_key);
        memcpy(iv, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void cbc_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)
{
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    int num_blocks = (ciphertext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned char block[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++)
    {
        AES_decrypt(ciphertext + i * BLOCK_SIZE, block, &aes_key);
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
            plaintext[i * BLOCK_SIZE + j] = block[j] ^ iv[j];
        }
        memcpy(iv, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void cfb_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned char block[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++)
    {
        AES_encrypt(iv, block, &aes_key);
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
            ciphertext[i * BLOCK_SIZE + j] = plaintext[i * BLOCK_SIZE + j] ^ block[j];
        }
        memcpy(iv, block, BLOCK_SIZE);
    }
}

void cfb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)
{
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    int num_blocks = (ciphertext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned char block[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++)
    {
        AES_encrypt(iv, block, &aes_key);
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
            plaintext[i * BLOCK_SIZE + j] = ciphertext[i * BLOCK_SIZE + j] ^ block[j];
        }
        memcpy(iv, block, BLOCK_SIZE);
    }
}

int main()
{
    unsigned char key[] = "my_secret_key";
    unsigned char iv[] = "my_initialization_vector";
    unsigned char plaintext[] = "This is a secret message";
    int plaintext_len = strlen(plaintext);

    // Pad the plaintext to a multiple of the block size
    int padded_len = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    unsigned char padded_plaintext[padded_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, 0, padded_len - plaintext_len);
}