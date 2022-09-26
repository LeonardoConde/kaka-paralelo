#include "mpi.h"
#include <stdio.h>
#include <string.h>
#define TAM 1

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

int main(int argc, char *argv[])
{
    int meu_ranque, num_procs, i, raiz = 0;
    int vet_envia [TAM] ; /* Vetor a ser enviado */
    int vet_recebe [TAM]; /* Vetor a ser recebido */
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Preenche o vetor com o ranque vezes 100*/
    vet_envia[0] = meu_ranque*100;

    /* Faz a redução, somando todos os valores calculados */
    MPI_Reduce(vet_envia, vet_recebe, TAM, MPI_INT, MPI_SUM, raiz, MPI_COMM_WORLD);
    /* O processo raiz imprime o resultado da operação de redução */
    if (meu_ranque == raiz)
    {
        printf("\nSoma todos ranks é igual a %d\n", vet_recebe[0]);
    }
    MPI_Finalize();
}