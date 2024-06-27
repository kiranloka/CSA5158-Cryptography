#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
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
    int e = 31;
    int n = 3599;

    // Find p and q using trial-and-error
    int p, q;
    for (p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            q = n / p;
            break;
        }
    }

    printf("p = %d, q = %d\n", p, q);

    // Calculate f(n) = (p-1)*(q-1)
    int f_n = (p - 1) * (q - 1);

    // Calculate the private key d using the extended Euclidean algorithm
    int d = modInverse(e, f_n);

    printf("Private key d = %d\n", d);

    return 0;
}