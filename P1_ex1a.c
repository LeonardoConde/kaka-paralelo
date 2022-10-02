#include <stdio.h>
#include <omp.h>
/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

#define NUM_THREADS 4

int main() {
    int x, soma = 0, subtracao = 0, mult = 1, TAM = 1000;
    int vet[TAM];
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for
    for (x = 0; x < 10; x++) {
        vet[x] = x + 1;
    }
    #pragma omp parallel for
    for (x = 0; x < 10; x++) {
        printf("vet[%d] = %d\n", x, vet[x]);
    }
    #pragma omp parallel for
    for (x = 0; x < 10; x++) {
        soma = soma + vet[x];
        subtracao = subtracao - vet[x];
        mult = mult * vet[x];
    }


    printf("Soma = %d\n", soma);
    printf("Subtracao = %d\n", subtracao);
    printf("Multiplicacao = %d\n", mult);
}