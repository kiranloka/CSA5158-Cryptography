#include <stdio.h>
#include <string.h>

void encrypt(char plaintext[],char cipherText[],char substitution[]){
    int  i;
    for(int i=0;plaintext[i]!='\0';++i){
        if(plaintext[i]>'a' && plaintext[i]<'z'){
            cipherText[i]=substitution[plaintext[i]-'a'];

        }else if (plaintext[i]>'A' && plaintext[i]<'Z'){
            cipherText[i]=substitution[plaintext[i]-'A']-32 ;//Uppercase letters
        }else{
            cipherText[i]=plaintext[i];
        }

    }
    cipherText[i]='\0';
}


int main(){
    char substitution[26] = {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 
        'X', 'C', 'V', 'B', 'N', 'M'
    };

    char plaintext[100];
    char ciphertext[100];

    // Input plaintext from user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, substitution);

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
