#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string encipher(string text, string key);
int main(int argc, string argv[]) {

    if (argc != 2) {  // certified that is only one comand line argument
        printf("usage: ./substitution KEY");
        return 1;
    }
    else { // certified that the key contains exactly 26 characters
        if (strlen(argv[1]) != 26) {
            printf("Key must contain 26 characters");
            return 1;
        }
        else { // certified the key has only alphabetic characters and that has no duplicate characters
            for (int i = 0, n = strlen(argv[1]); i < n; i++) {
                if (!isalpha(argv[1][i])) {
                    printf("Key must only contains alphabetic characters");
                    return 1;
                }
                for (int j = i + 1; j < n; j++) {
                    if (argv[1][i] == argv[1][j]) {
                        printf("Duplicate characters");
                        return 1;
                    }
                }
            }

        }

    }
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    string ciphertext = encipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}

string encipher(string text, string key) {
    int textLength = strlen(text);
    int keyLength = strlen(key);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(text[i])) {
          if (isupper(text[i])) {
              text[i] = toupper(key[text[i] - 65]);
          }
          else {
              text[i] = tolower(key[text[i] - 97]);
          }
        }

    }

    return text;
}