#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string cipherCaesar(string text, int k);

int main(int argc, string argv[]) {
    int key;
    // Verifica a quantidade de itens na linha de comando
    if (argc != 2) {
        printf("Erro: Digite a chave");
        return 1;
    }

    // Quantidade correta de itens: ./caesar argumento(chave)
    else {
        // Verifica se o valor da chave é válido
        for (int i = 0, n = strlen(argv[1]); i < n; i++) {

            if (isdigit(argv[1][i]) == false) {
                printf("Use: ./caesar key");
                return 1;
            }
        }

        key = atoi(argv[1]);

    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = cipherCaesar(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
    return 0;

}


string cipherCaesar(string text, int k) {  //text é um vetor de caracteres

    for (int i = 0, n = strlen(text); i < n; i++) {

        if (isalpha(text[i])) {
            if (islower(text[i])) {
                text[i] = ((text[i] - 97) + k) % 26 + 97;
            }
            else if (isupper(text[i])) {
                text[i] = ((text[i] - 65) + k) % 26 + 65 ;
            }
        }
    }

    return text;
}
