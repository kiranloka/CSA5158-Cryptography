#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_N_PLAINTEXTS 10

// Frequency of letters in English (A-Z)
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074};

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequencies(const char *text, double *frequencies)
{
    int length = strlen(text);
    int letterCounts[ALPHABET_SIZE] = {0};
    int totalLetters = 0;

    // Count each letter in the ciphertext
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            char letter = tolower(text[i]);
            letterCounts[letter - 'a']++;
            totalLetters++;
        }
    }

    // Calculate the frequency of each letter
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        frequencies[i] = (double)letterCounts[i] / totalLetters * 100;
    }
}

// Function to decrypt the ciphertext using a given key
void decrypt(const char *ciphertext, char *plaintext, int key)
{
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset - key + ALPHABET_SIZE) % ALPHABET_SIZE) + offset;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Function to calculate the chi-squared statistic for a given plaintext
double calculateChiSquared(const char *plaintext)
{
    double frequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(plaintext, frequencies);
    double chiSquared = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        double expected = englishFrequencies[i];
        double observed = frequencies[i];
        chiSquared += ((observed - expected) * (observed - expected)) / expected;
    }

    return chiSquared;
}

// Structure to hold plaintexts and their chi-squared values
typedef struct
{
    char plaintext[1024];
    double chiSquared;
} Plaintext;

// Function to compare two plaintexts based on their chi-squared values
int comparePlaintexts(const void *a, const void *b)
{
    Plaintext *pa = (Plaintext *)a;
    Plaintext *pb = (Plaintext *)b;
    return (pa->chiSquared > pb->chiSquared) - (pa->chiSquared < pb->chiSquared);
}

int main()
{
    // Sample ciphertext
    const char *ciphertext = "GCUA VQ DTGCM";
    int length = strlen(ciphertext);
    char plaintext[length + 1];
    Plaintext plaintexts[ALPHABET_SIZE];

    // Decrypt the ciphertext with all possible keys and calculate chi-squared values
    for (int key = 0; key < ALPHABET_SIZE; key++)
    {
        decrypt(ciphertext, plaintext, key);
        double chiSquared = calculateChiSquared(plaintext);
        strcpy(plaintexts[key].plaintext, plaintext);
        plaintexts[key].chiSquared = chiSquared;
    }

    // Sort plaintexts based on chi-squared values
    qsort(plaintexts, ALPHABET_SIZE, sizeof(Plaintext), comparePlaintexts);

    // Output the top N plaintexts
    int topN = TOP_N_PLAINTEXTS;
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++)
    {
        printf("Key %d: %s (Chi-Squared: %.2f)\n", i, plaintexts[i].plaintext, plaintexts[i].chiSquared);
    }

    return 0;
}
