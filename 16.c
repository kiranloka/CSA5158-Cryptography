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

// Structure to hold plaintexts and their chi-squared values
typedef struct
{
    char plaintext[1024];
    double chiSquared;
} Plaintext;

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

// Function to calculate the chi-squared statistic for a given frequency analysis
double calculateChiSquared(const double *observed, const double *expected)
{
    double chiSquared = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        chiSquared += ((observed[i] - expected[i]) * (observed[i] - expected[i])) / expected[i];
    }

    return chiSquared;
}

// Function to decrypt the ciphertext using a given key mapping
void decrypt(const char *ciphertext, char *plaintext, const char *keyMap)
{
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = keyMap[tolower(ciphertext[i]) - 'a'] - 'a' + offset;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

// Function to generate possible plaintexts using frequency analysis
void generatePossiblePlaintexts(const char *ciphertext, Plaintext *plaintexts, int topN)
{
    double ciphertextFrequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, ciphertextFrequencies);

    // Initialize key mapping with English frequency order
    char keyMap[ALPHABET_SIZE + 1] = "etaoinshrdlcumwfgypbvkjxqz";

    for (int shift = 0; shift < ALPHABET_SIZE; shift++)
    {
        char currentKeyMap[ALPHABET_SIZE + 1];
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            currentKeyMap[i] = 'a' + (keyMap[(i + shift) % ALPHABET_SIZE] - 'a');
        }
        currentKeyMap[ALPHABET_SIZE] = '\0';

        decrypt(ciphertext, plaintexts[shift].plaintext, currentKeyMap);
        plaintexts[shift].chiSquared = calculateChiSquared(ciphertextFrequencies, englishFrequencies);
    }

    // Sort plaintexts based on chi-squared values
    qsort(plaintexts, ALPHABET_SIZE, sizeof(Plaintext), comparePlaintexts);
}

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
    Plaintext plaintexts[ALPHABET_SIZE];

    // Generate possible plaintexts using frequency analysis
    generatePossiblePlaintexts(ciphertext, plaintexts, TOP_N_PLAINTEXTS);

    // Output the top N plaintexts
    printf("Top %d possible plaintexts:\n", TOP_N_PLAINTEXTS);
    for (int i = 0; i < TOP_N_PLAINTEXTS; i++)
    {
        printf("Plaintext: %s (Chi-Squared: %.2f)\n", plaintexts[i].plaintext, plaintexts[i].chiSquared);
    }

    return 0;
}
