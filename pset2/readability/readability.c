# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

int countLetters(string texto);
int countWords(string texto);
int countSentences(string texto);
float calcIndex(int l, int w, int s);
bool isEndSentenceChar(char character);

int main(void) {
    string texto = get_string("Texto: ");
    int l = countLetters(texto);
    int w = countWords(texto);
    int s = countSentences(texto);
    float indice = calcIndex(l, w, s);
    //Regras de nota:
    if (indice < 1) {
        printf("Before Grade 1\n");
    }
    else if (indice >= 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", (int) round(indice));
    }

}

float calcIndex(int l, int w, int s) {

    float L = 100.0 * l / w;
    float S = 100.0 * s / w;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return index;

}

int countLetters(string texto) { //Contagem de letras do alfabeto no texto

    int counter = 0;
    //Percorrer o texto
    for (int i = 0, n = strlen(texto); i < n; i++) {
        // Contagem de letras usando a função isalpha
        if (isalpha(texto[i])) {
            counter++;
        }
    }
    return counter;
}


int countWords(string texto) {
    int counter = 0;
    //Percorrer o texto
    for(int i = 0, n = strlen(texto); i < n; i++) {
        //Cada palavra é separada por um espaço
        if (isspace(texto[i])) {
            counter++;
        }
    }
    return (counter + 1); // Entre um espaço tem duas palavras
}

int countSentences(string texto){
    // Contagem de sentenças. Separadas por "." "!" "?" contagem de pontuação = qtd de sentenças
    int counter = 0;
    for(int i = 0, n = strlen(texto); i < n; i++) {
        if (isEndSentenceChar(texto[i])) {
            counter++;
        }
    }
    return counter;
}

bool isEndSentenceChar(char character) {
    return character == '!' || character == '?' || character == '.';
}