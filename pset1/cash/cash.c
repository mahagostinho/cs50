#include <stdio.h>
#include <cs50.h>
#include <math.h>

float getCash(void);

int main(void)
{
    //Obtém o valor do troco inserido pelo usuário através da função getCash
    float reais = getCash();

    //Transforma o valor fornecido em reais (decimal) em centavos (inteiro)
    int cent = round(reais * 100);

    // Inicializando o contador para armazenar a quantidade de moedas necessárias
    int counter = 0;

    //A partir do valor inteiro de centavos retirar da maior moeda 25 até a menor (10, 5 e 1)
    // a cada subtração o contador é incrementado uma unidade até que o valor de cent seja zero
    while (cent >= 25)
    {
        cent = cent - 25;
        counter++;
    }

    while (cent >= 10 && cent < 25)
    {
        cent = cent - 10;
        counter++;
    }

    while (cent >= 5 && cent < 10)
    {
        cent = cent - 5;
        counter++;
    }

    while (cent >= 1 && cent < 5)
    {
        cent = cent - 1;
        counter++;
    }

    //Retorna a quantidade de moedas
    printf("%i \n", counter);
}

float getCash(void)
{
    float cash;

    do
    {

        cash = get_float("Qual o valor do troco?");

    }
    while (cash < 0);  //Enquanto o usuário não inserir um decimal não negativo é solicitado uma nova entrada

    return cash;
}