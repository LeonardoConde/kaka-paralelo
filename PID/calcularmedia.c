#include <stdio.h>
#include <stdlib.h>

#define TIME 5

float calcularMedia(FILE *arq);
void processarNotas();

int main(int argc, char * argv[])
{


    FILE *file;
    float resultado = 0.0;
    int erro = 0;
    int n = 0;
    int i;
    double time_spent;

    if (argc > 1)  {
        for (i=1; i<=argc; i++)
        {
            file =fopen(argv[i], "r");
            if (!file)
                erro = 1;
            else
            {
                resultado = calcularMedia(file);
                fclose(file);
                printf("arquivo %s\n",argv[i]);
                printf("Media das notas = %3.2f\n",resultado);
            }
        }
    }
    else
        printf("Arquivos de entrada nao localizados!!\n");

    return erro;
}

float calcularMedia(FILE *arq)
{

    float media = 0.0;
    float nota;
    char buf[1000];
    int i=0;

    while (fgets(buf,1000, arq)!=NULL)
    {
        nota = atof(buf);
        //printf("nota: %f\n",nota);
        media = media + nota;
        i++;
    }
    processarNotas();
    return media/i;
}

void processarNotas() {
     printf("Processo %d esta processando o resultado das notas....\n",getpid());
     sleep(TIME);
}



