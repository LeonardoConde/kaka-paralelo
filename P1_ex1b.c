#include <stdio.h>
#include "mpi.h"

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

#define TAM 10

enum funcoes_de_trabalho {Main = 0, Soma, Subtrai, Mult} funcao;

int main (int argc, char **argv){
    int rank, size, tag, i, meu_ranque, resultado = 0;
    int x, soma=0, subtracao=0, mult=1;
    int vet[TAM];

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if( size != 4) {
        if(meu_ranque == 0) printf("\nO programa deve ser rodado com 4 processos!\n\n");
        MPI_Finalize();
        return 0;
    }

    if (meu_ranque == Main) {
        for (x = 0; x < TAM; x++) {
            vet[x] = x + 1;
        }

        for (x = 0; x < TAM; x++) {
            printf("vet[%d] = %d\n", x, vet[x]);
        }

        MPI_Send(vet, TAM, MPI_INT, Soma, Soma, MPI_COMM_WORLD);
        MPI_Send(vet, TAM, MPI_INT, Subtrai, Subtrai, MPI_COMM_WORLD);
        MPI_Send(vet, TAM, MPI_INT, Mult, Mult, MPI_COMM_WORLD);
    } else{
        MPI_Recv(vet, TAM, MPI_INT, Main, meu_ranque, MPI_COMM_WORLD, &status);
        for( int i = 0; i < TAM; i++) {

            switch (meu_ranque) {
                case Soma:
                    soma += vet[i];
                    break;
                case Subtrai:
                    subtracao -= vet[i];
                    break;
                case Mult:
                    mult *= vet[i];
                    break;
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(meu_ranque != Main) {
        switch (meu_ranque) {
            case Soma:
                resultado = soma;
                break;
            case Subtrai:
                resultado = subtracao;
                break;
            case Mult:
                resultado = mult;
                break;
        }
        MPI_Send(&resultado, 1, MPI_INT, Main, Main, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&soma, 1, MPI_INT, Soma, meu_ranque, MPI_COMM_WORLD, &status);
        MPI_Recv(&subtracao, 1, MPI_INT, Subtrai, meu_ranque, MPI_COMM_WORLD, &status);
        MPI_Recv(&mult, 1, MPI_INT, Mult, meu_ranque, MPI_COMM_WORLD, &status);
        printf("Soma = %d\n", soma);
        printf("Subtracao = %d\n", subtracao);
        printf("Multiplicacao = %d\n", mult);
    }


    MPI_Finalize();
    return 0;

}