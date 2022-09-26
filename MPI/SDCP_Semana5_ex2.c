#include "mpi.h"
#include <stdio.h>
#include <string.h>

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito.
 */

int main(int argc, char *argv[])
{
    int i, valor, meu_ranque, raiz = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);

    valor = meu_ranque;
    if (meu_ranque == raiz)
    {
        valor = 12345;
    }
    MPI_Bcast(&valor, 1, MPI_INT, raiz, MPI_COMM_WORLD);
    printf("O processo com ranque %d recebeu o valor: %d\n",meu_ranque, valor);
    MPI_Finalize();
    return 0;
}