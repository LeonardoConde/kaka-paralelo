#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 800

void inicializarMatriz(int m[MAX][MAX], int n);
void exibirMatriz(int m[MAX][MAX], int n);

int main(void)
{
    int n, i, j, k;
    int m1[MAX][MAX], m2[MAX][MAX], m3[MAX][MAX];

    n = MAX;

    srand(time(NULL));
    inicializarMatriz(m1,n);
    inicializarMatriz(m2,n);
    //exibirMatriz(m1,n);
    //exibirMatriz(m2,n);
    printf("Tamanho da matriz: %d\n",MAX);
    printf("\nTotal de threads executando: %d\n", omp_get_num_threads());
    double st=omp_get_wtime();
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            
            for (k = 0, m3[i][j] = 0; k < n; k = k + 1)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
    double en=omp_get_wtime();
    printf("Tempo do processamento: %lf\n",en-st);
    printf("\nCalculo finalizado!\n");
    return 0;
}

void inicializarMatriz(int m[MAX][MAX], int n) {

    int i,j;


    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
           m[i][j] = rand()%100;
}

void exibirMatriz(int m[MAX][MAX], int n) {

    int i,j;

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++)
           printf("%d  ",m[i][j]);
        printf("\n");
    }
    printf("\n\n");

}

