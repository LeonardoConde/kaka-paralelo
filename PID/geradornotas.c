#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[])
{
    FILE *file;
    float nota;
    int i;
    time_t t;
    int erro = 0;

    if (argc > 1)
    {

        file =fopen(argv[1], "w");

        if (!file)
            erro = 1;
        else
        {

            srand((unsigned int)time(NULL));
            for (i=1; i<=50; i++)
            {
                nota = ((float)rand()/(float)(RAND_MAX)) * 10.0;
                fprintf(file,"%3.2f\n", nota);
            }

            fclose(file);
            printf("Arquivo gerado com sucesso!!\n");
        }


    } else
          printf("Faltou o nome do arquivo de saida!\n");


    return erro;
}
