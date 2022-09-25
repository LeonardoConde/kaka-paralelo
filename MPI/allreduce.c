#include <math.h>
#include "mpi.h"
#define NELEM 1024
int main(int argc, char *argv[])
{
    int i, meu_ranque, num_procs;
    float *nums_aleat = NULL;
    float media, dif_quad_local = 0, soma_local = 0;
    float soma_global, dif_quad_global, desvio_padrao;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Alimenta o gerador de n�meros aleat�rios com valores diferentes para cada processo */
    srand(MPI_Wtime()*meu_ranque);
    /* Cria um vetor de n�meros aleat�rios em todos os processos. Cada n�mero tem um valor entre 0 e 1 */
    nums_aleat = (float *)malloc(sizeof(float) * NELEM);
    for (i = 0; i < NELEM; i++)
        nums_aleat[i] = (rand() / (float)RAND_MAX);
    /* Soma os n�meros localmente */
    for (i = 0; i < NELEM; i++)
        soma_local += nums_aleat[i];
    /* Imprime a soma e m�dia dos n�meros aleat�rios em cada processo */
    printf("Soma local para o processo %d - %f, media local = %f\n", meu_ranque, soma_local, soma_local / NELEM);
           /* Reduz todas as somas locais em uma soma global para poder calcular a m�dia */
           MPI_Allreduce(&soma_local, &soma_global, 1, MPI_FLOAT,MPI_SUM, MPI_COMM_WORLD);
           media = soma_global / (NELEM * num_procs);
           /* Computa a soma local do quadrado das diferen�as da m�
           dia */
           for (i = 0; i < NELEM; i++)
           dif_quad_local += (nums_aleat[i] - media) * (nums_aleat[i]
                             - media);
           /* Reduz a soma global do quadrado das diferen�as locais para o processo raiz imprimir a resposta */
           MPI_Reduce(&dif_quad_local, &dif_quad_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
           /* O desvio padr�o � a raiz quadrada da m�dia do quadrado das diferen�as */
           if (meu_ranque == 0)
    {
        desvio_padrao = sqrt(dif_quad_global/(NELEM *num_procs));
            printf("M�dia - %f, Desvio padr�o = %f\n", media,desvio_padrao);
        }
    /* Libera espa�o do vetor */
    free(nums_aleat);
    MPI_Finalize();
    return 0;
}

