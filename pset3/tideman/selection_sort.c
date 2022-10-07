#include <cs50.h>
#include <stdio.h>

int array[8] = {6, 3, 8, 5, 2, 7, 4, 1};

int main(void) {

    for (int i = 0; i < 8 - 1; i++) {
        int menor = array[i];
        int maior = 0;
        for (int j = i + 1; j < 8; j++) {
            if (array[j] < menor) {
                menor = array[j];
                maior = array[i];
                array[i] = menor;
                array[j] = maior;
            }
        }

    }
    for (int i = 0; i < 8; i++) {
        printf("%i, ",array[i]);
    }
    printf("\n");
}