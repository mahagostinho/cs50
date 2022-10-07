        # include <stdio.h>
# include <cs50.h> //adicionar a biblioteca do CS50

int main(void)
{
    //get_string é uma função específica da biblioteca do cs50
    string nome = get_string("Qual é o seu nome? \n");
    printf("Hello, %s! \n",nome);
}