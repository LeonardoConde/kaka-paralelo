#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

void dense_mat_vec(int m, int n, double *x, double *A, double *y);

int main() {
    srand(time(NULL));

    int m, n;           // usuario input
    double *x, *y;      // calcular tam com m e n e atribuir valores aleatorios
    double **A;         // calcular dimensoes com m e n e atribuir valores aleatorios


    // aceita os valores de m e n da linha de comando em tempo de execução
    printf("\nNúmero de linhas: ");
    scanf("%d", &m);
    printf("Número de colunas: ");
    scanf("%d", &n);

    // Verificação da atribuição
    printf("Linhas: %d, Colunas: %d\n", m, n);

    // aloca os vetores x e y
    x = malloc(m * sizeof(int));
    y = malloc(n * sizeof(int));

    // aloca a matriz A
    A = malloc(m * sizeof(int *));
    #pragma omp parallel for
    for (int i = 0; i < m; ++i) {
        A[i] = malloc(n * sizeof(int));
    }

    // inicializa y com alguns valores adequados
    printf("\nInicializa valores no Y e A");
    printf("\nVetor Y: ");
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        y[i] = rand() % 10;;
        printf("%0.1lf ", y[i]);
    }

    // inicializa A com alguns valores adequados
    printf("\n\nMatriz A: ");
    #pragma omp parallel for
    for (int lin = 0; lin < m; lin++) {
        printf("\n");
        for (int col = 0; col < n; col++) {
            A[lin][col] = rand() % 10;
            printf("%0.1lf ", A[lin][col]);
        }
    }

    printf("\n");

    // chama a função dense_mat_vec
    dense_mat_vec(m, n, x, *A, y);


    // prints para ver resultado do X depois
    printf("\nPrint para ver resultado depois");
    printf("\nVetor X: ");
    #pragma omp parallel for
    for (int i = 0; i < m; ++i) {
        printf("%0.1lf ", x[i]);
    }
    printf("\n");

    // libera memória
    free(x);
    free(y);
    free(A);
    return 0;
}


void dense_mat_vec(int m, int n, double *x, double *A, double *y) {
    int i, j;
    #pragma omp parallel for
    for (i = 0; i < m; i++) {
        double tmp = 0.0;
        for (j = 0; j < n; j++)
            tmp += A[i * n + j] * y[j];
        x[i] = tmp;
    }

}