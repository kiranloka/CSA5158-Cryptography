//This is the 7th program in the word document

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 1024

// Function to count the frequency of each character in the ciphertext
void frequencyAnalysis(const char* ciphertext, int* freq) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || ispunct(ciphertext[i])) {
            freq[(int)ciphertext[i]]++;
        }
    }
}

// Function to print character frequencies
void printFrequencies(const int* freq) {
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("Character '%c' appears %d times\n", i, freq[i]);
        }
    }
}

// Function to substitute characters based on a provided key
void substitute(const char* ciphertext, const char* key, char* plaintext) {
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || ispunct(ciphertext[i])) {
            for (j = 0; key[j] != '\0'; j++) {
                if (ciphertext[i] == key[j]) {
                    plaintext[i] = 'a' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_SIZE] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[128] = {0};
    char plaintext[MAX_TEXT_SIZE];
    char key[] = "ETAOINSRHLDCUMFPGWYBVKXJQZ";  // Example key, needs adjustment

    frequencyAnalysis(ciphertext, freq);
    printFrequencies(freq);

    // Substitution decryption
    substitute(ciphertext, key, plaintext);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}
