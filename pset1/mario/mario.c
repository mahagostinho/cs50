# include <stdio.h>
# include <cs50.h>

int getInt(void);

int main(void)
{
    int h = getInt();

    // Criando a quantidade de linhas
    for (int i = 0; i < h ; i++)
    {
        //Inserindo a quantidade de caracteres # por linha
        // Primeiro laço subindo a pirâmide
        for (int j = 0; j < h; j++)
        {
            if (j + i < h - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // Insere espaço "buraco"
        printf("  ");

        //Início de outro laço para descer a pirâmide
        for (int j = 0; j < h; j++)
        {
            if (j <= i)
            {
                printf("#");
            }

        }


        //Após a impressão de uma linha, saltar a linha para começar uma nova até que i seja igual a h, onde para a criação de novas linhas
        printf("\n");
    }
}

int getInt(void)
{
    int heigth;
    do
    {
        //Solicita ao usuário a altura da pirâmide
        heigth = get_int("Insira a altura da pirâmide:");

    }
    while (heigth < 1 || heigth > 8);  // Checa se a altura está dentro dos limites especificados

    return heigth;

}