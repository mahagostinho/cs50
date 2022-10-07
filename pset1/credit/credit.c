#include <stdio.h>
#include <cs50.h>
#include <string.h>

long getNumber(void);

int getDigit(long number);

int checksum(long number, int digits);

string bandeiraCartao(long number, int digits, int sum);

int main(void) {

    long number = getNumber(); //Ler o número do cartão

    int digits = getDigit(number); // Retorna a quantidade de dígitos do cartão

    int sum = checksum(number, digits); //Retorna o valor da soma dos dígitos

    string bandeira = bandeiraCartao(number, digits, sum); // Verifica se o cartão é válido de acordo com o Algoritmo de Luhn
                                                           // Verifica a bandeira do cartão de acordo com as regras de dígitos
    printf("%s\n", bandeira);

}

long getNumber(void) {

    long number;

    do {

        number = get_long("Insira o número do cartão:");

    }
    while (number < 0);

    return number;

}

int getDigit(long number) {

    int counter = 0;

    while (number != 0)
    {

        number = number / 10;

        counter++;

    }

    return counter;
}

int checksum(long number, int digits){

    long n = number;
    long r, dobro, r2, n2;
    int sum = 0;

    for (int k = 0; k < digits; k++) {  // Multiplique cada segundo digito por 2, começando com o penúltimo dígito do número

        r = n % 10;
        n = n / 10;

        if (k % 2 != 0) {

            dobro = 2 * r;

            if (dobro < 10) {

                sum = sum + dobro;

            }
            else {  // n2 = r = 12;  r2 = 2

                n2 = dobro;

                while (n2 != 0) {

                    r2 = n2 % 10;
                    n2 = n2 / 10;
                    sum = sum + r2;
                }

            }

        }
        else {

            sum = sum + r;

        }
    }

    return sum;
}

string bandeiraCartao(long number, int digits, int sum) {

    string bandeira = "";

    if (digits < 13 || digits > 16) {  // Primeiro verifica se a qtd de dígitos corresponde a alguma das bandeiras

        bandeira = "INVALID";

    }
    else {  //Se não for inválido pela quantidade de dígitos, verificar Checksum

        if (sum % 10 == 0) {  // Se o último dígito do total for 0, o número é válido pelo checksum!

            // Sabendo que o número é válido, determinar a bandeira do cartão
            // Primeiro conseguir o primeiro e os dois primeiros dgitos do cartão

            long aux2 = 1;

            for (int i = 0; i < digits - 2; i++) {

                aux2 = aux2 * 10;

            }

            long twoDig = number / aux2;  // 1º + 2º dígitos

            long aux1 = 1;
            for (int i = 0; i < digits - 1; i++) {

                aux1 = aux1 * 10;

            }

            long firstDig = number / aux1;  // 1º dígit

            if (digits == 15 && (twoDig == 34 || twoDig == 37)) {

                bandeira = "AMEX";

            }
            else if (digits == 13 && firstDig == 4) {

                bandeira = "VISA";

            }
            else if (digits == 16) {

                if (firstDig == 4) {

                    bandeira = "VISA";

                }
                else if (twoDig == 51 || twoDig == 52 || twoDig == 53 || twoDig == 54 || twoDig == 55) {

                    bandeira = "MASTERCARD";

                }
                else {

                    bandeira = "INVALID";

                }

            }
            else {

                bandeira = "INVALID";

            }
        }

        else {  // Se o último dígito do total for diferente de 0, o número é inválido pelo checksum!

            bandeira = "INVALID";

        }
    }

    return bandeira;

}

