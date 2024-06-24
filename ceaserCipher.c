#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ceaserCipher(char *text, int k)
{
    char ch;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        ch = text[i];
        if (isupper(ch))
        {
            ch = ((ch - 'A' + k) % 26) + 'A';
        }
        else if (islower(ch))
        {
            ch = ((ch = 'a' + k) % 26) + 'a';
        }
        text[i] = ch;
    }
}
int main()
{
    char text[100];

    int k;

    printf("Enter the character: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the value of k(1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25)
    {
        printf("Invalid value of k inuput should be in the range 1 to 25");
        return 1;
    }

    ceaserCipher(text, k);

    printf("Encrypted data:%s\n ", text);

    return 0;
}