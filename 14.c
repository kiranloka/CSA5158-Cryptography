// Vignere Cipher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Function to generate a random key of the same length as the plaintext
void generateRandomKey(int key[], int length)
{
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        key[i] = rand() % 26;
    }
}

// Function to encrypt the plaintext using the one-time pad version of the Vigenère cipher
void encrypt(const char *plaintext, char *ciphertext, const int key[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - offset + key[i]) % 26) + offset;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt the ciphertext using the one-time pad version of the Vigenère cipher
void decrypt(const char *ciphertext, char *plaintext, const int key[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset - key[i] + 26) % 26) + offset;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0'; // Null-terminate the plaintext
}

int main()
{
    // Sample plaintext
    const char *plaintext = "meet me at the usual place at ten rather than eight oclock";
    int length = strlen(plaintext);
    int key[length];
    char ciphertext[length + 1];
    char decryptedText[length + 1];

    // Generate random key
    generateRandomKey(key, length);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, key, length);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedText, key, length);

    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Generated Key: ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
