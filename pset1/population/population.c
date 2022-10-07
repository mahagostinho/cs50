#include <stdio.h>
#include <cs50.h>

long popInicial(void);
long popFinal(long n);

int main(void) {

    long n = popInicial();

    long f = popFinal(n);

    int y = 0;

    long tot;

    if (n == f) {
        y = 0;
    }
    else {

        do {

            tot = n + n/3 - n/4;
            n = tot;
            y++;

        }
        while (tot < f);

    }

    printf("Years: %i\n", y);

}

long popInicial(void) {

    long n;

    do {

        n = get_long("Tamanho inicial da população: ");

    }
    while (n < 9);

    return n;

}

long popFinal(long n) {

    long f;

    do {

        f = get_long("Tamanho final da população: ");

    }
    while (f < n);

    return f;

}