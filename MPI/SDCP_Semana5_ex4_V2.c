#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

#define TAM_VET 10
int main(int argc, char *argv[])
{
    int i, meu_ranque, num_procs, raiz = 0;
    int *vet_envia, vet_recebe[TAM_VET];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    int num_workers = num_procs - 1;

    if (meu_ranque == raiz)
    {
        vet_envia = (int*)malloc (num_workers*TAM_VET*sizeof(int));
        //Só inicia o array
        for (i = 0; i < (TAM_VET*num_workers); i++) vet_envia[i] = 0;
    }

    if (meu_ranque == raiz) {
        printf("\nScatter Process:\n");
    }
    //Distribui igualmente
    MPI_Scatter(vet_envia, TAM_VET, MPI_INT, vet_recebe,TAM_VET, MPI_INT, raiz, MPI_COMM_WORLD);
    printf("Processo = %d, atribuiu", meu_ranque);
    for (i = 0; i < TAM_VET; i ++) {
        vet_recebe[i] = (TAM_VET * meu_ranque) + i + 1;
        printf(" %d",  vet_recebe[i]);
    }
    printf("\n");

    //Espera todos
    MPI_Barrier(MPI_COMM_WORLD);
    //Coleta todos
    MPI_Gather (vet_recebe, TAM_VET, MPI_INT, vet_envia,TAM_VET, MPI_INT, raiz, MPI_COMM_WORLD);

    if (meu_ranque == raiz)
    {
        printf("\nGather Process:\n");
        printf("Processo raiz, recebeu: ");
        for (i = 0; i < (num_procs*TAM_VET); i ++) printf(" %d", vet_envia[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}