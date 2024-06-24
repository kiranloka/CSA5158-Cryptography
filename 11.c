#include <stdio.h>
#include <math.h>

int main() {
    int i;
    double log2_factorial = 0.0;

    // Sum log2(i) for i from 1 to 25
    for (i = 1; i <= 25; i++) {
        log2_factorial += log2(i);
    }

    // Convert the log2 factorial to an approximate power of 2
    double num_keys = pow(2, log2_factorial);

    printf("Approximate number of possible keys for the Playfair cipher: 2^%.2f\n", log2_factorial);

    return 0;
}
