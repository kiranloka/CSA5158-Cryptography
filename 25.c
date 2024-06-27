#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

// Function to calculate the modular exponentiation
int modExp(int base, int exponent, int modulus)
{
    int result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent / 2;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to encrypt a plaintext block using RSA
int ciphertext(int plaintext, int e, int n)
{
    return modExp(plaintext, e, n);
}

int plaintext(int ciphertext, int d, int n)
{
    return modExp(ciphertext, d, n);
}

// Function to calculate the modular multiplicative inverse using the extended Euclidean algorithm
int modInverse(int a, int m)
{
    int m0 = m;
    int x, y;
    int q, temp;

    if (gcd(a, m) != 1)
    {
        printf("Modular inverse does not exist\n");
        return -1;
    }

    x = 0;
    y = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        q = a / m;
        temp = m;
        m = a % m;
        a = temp;
        temp = x;
        x = y - q * x;
        y = temp;
    }

    if (y < 0)
        y += m0;

    return y;
}

int main()
{
    int n = 3599; // public modulus
    int e = 31;   // public exponent
    int num_blocks = 5;
    int plaintext[num_blocks] = {123, 456, 789, 234, 567}; // plaintext blocks
    int ciphertext_blocks[num_blocks];

    // Encrypt the plaintext blocks using RSA
    for (int i = 0; i < num_blocks; i++)
    {
        ciphertext_blocks[i] = ciphertext(plaintext[i], e, n);
    }

    // Assume someone tells us that one of the plaintext blocks has a common factor with n
    int common_factor = -1;
    for (int i = 0; i < num_blocks; i++)
    {
        int gcd_val = gcd(plaintext[i], n);
        if (gcd_val > 1 && gcd_val < n)
        {
            common_factor = gcd_val;
            break;
        }
    }

    if (common_factor == -1)
    {
        printf("No common factor found\n");
        return 1;
    }

    // Factorize n using the common factor
    int p = common_factor;
    int q = n / p;

    printf("p = %d, q = %d\n", p, q);

    // Now that we have p and q, we can calculate the private key d
    int f_n = (p - 1) * (q - 1);
    int d = modInverse(e, f_n);

    printf("Private key d = %d\n", d);

    return 0;
}