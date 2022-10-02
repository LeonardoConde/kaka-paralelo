#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mpi.h"


/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

#define TAM_VET_GLOBAL 40

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int i, meu_ranque, num_procs, raiz = 0;
    double media_total = 0.0;
    int vet_envia[TAM_VET_GLOBAL];
    int vet_recebe[10], recebe_sum_media[1] = {0};
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int tam_vet = TAM_VET_GLOBAL / (num_procs - 1);
    int tam_resto_vet = TAM_VET_GLOBAL % (num_procs - 1);

    if (meu_ranque == raiz) {
        //Só inicia o array
        printf("Tamanho do vetor: %d, Número de processos: %d\n", TAM_VET_GLOBAL, num_procs);
        printf("Tam vet: %d, Tam Resto: %d\n", tam_vet, tam_resto_vet);
        printf("Array: ");
        for (i = 0; i < (TAM_VET_GLOBAL); i++) {
            vet_envia[i] = rand() % 10;
            printf("%d ", vet_envia[i]);
        }
        printf("\n");
    }

    //Distribui igualmente
    MPI_Bcast(vet_envia, TAM_VET_GLOBAL, MPI_INT, 0, MPI_COMM_WORLD);


    int soma[1] = {0};
    int inicio = (meu_ranque * tam_vet);

    if (meu_ranque != num_procs - 1) {
        for (i = inicio; i < inicio + tam_vet; i++) {
            soma[0] += vet_envia[i];
        }
    } else {
        for (i = inicio; i < TAM_VET_GLOBAL; i++) {
            soma[0] += vet_envia[i];
        }
    }

    printf("\nRank: %d, Soma do vetor: %d\n", meu_ranque, soma[0]);

    MPI_Reduce(&soma, &recebe_sum_media, 1, MPI_INT, MPI_SUM, raiz, MPI_COMM_WORLD);

    if (meu_ranque == raiz) {
        printf("A soma total: %d\n", recebe_sum_media[0]);

        media_total = (double) recebe_sum_media[0] / TAM_VET_GLOBAL;
        printf("\nA média resulta em: %lf\n", media_total);
    }

    MPI_Finalize();
    return 0;
}