#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define MATRIX_SIZE_TO_SHOW 6
#define VECTOR_SIZE_TO_SHOW 100

//Structs
typedef enum {
    FALSE, TRUE
} bool;


//Functions List

int genRandomMatrix(int n, int matrix[n][n]);

int genRandomVector(int n, int vector[n]);

int multiplicaMatriz(int n, int a[n][n], int b[n][n], int result[n][n]);

int produtoEscalarThread(int vetor_U[], int vetor_V[], int numThreads);

int multiplicaMatrizThread(int n, int matrixA[n][n], int matrixB[n][n], int result[n][n], int numThread);

int produtoEscalarThread(int vetor_U[], int vetor_V[], int numThreads);

void printMatrix(int n, int matrix[n][n]);

void printVetor(int vetorX[]);

//List Exercicios
double ex1_etapa1(int n, bool isToPrint);

void ex1_etapa2();

double ex1_etapa3(int n, int numThread, bool isToPrint);

void ex1_etapa4();

void ex1_etapa5();

double ex2_etapa1(int n, bool isToPrint);

void ex2_etapa2();

double ex2_etapa3(int n, int numTreads, bool isToPrint);

void ex2_etapa4();

void ex2_etapa5();

//Exercicios:
void exercicio1() {
    printf("Ex 1:");
    ex1_etapa1(MATRIX_SIZE_TO_SHOW, TRUE);
    ex1_etapa2();
    ex1_etapa3(MATRIX_SIZE_TO_SHOW, 4, TRUE);
    ex1_etapa4();
    ex1_etapa5();
}

void exercicio2() {
    printf("\n\nEx 2:");
    ex2_etapa1(VECTOR_SIZE_TO_SHOW, TRUE);
    ex2_etapa2();
    ex2_etapa3(VECTOR_SIZE_TO_SHOW, 4, TRUE);
    ex2_etapa4();
    ex2_etapa5();
}

//Main
int main(void) {
    system("clear");
    srand(time(NULL));
    exercicio1();
    exercicio2();
    printf("\n\nFim!!!\n");
    return 0;
}

//Matrix functions
int genMatrixEmpty(int n, int matrix[n][n]) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++)
            matrix[y][x] = 0;
    }
    return 1;
}

int genRandomMatrix(int n, int matrix[n][n]) {
    for (int linha = 0; linha < n; linha++) {
        for (int coluna = 0; coluna < n; coluna++) {
            matrix[linha][coluna] = rand() % 10;
        }
    }
    return 1;
}

int genRandomVector(int n, int vector[n]) {
    for (int linha = 0; linha < n; linha++) vector[linha] = rand() % 10;
    return 1;
}

int genMatrixByFile(int n, int a[n][n], const char *filename) {
    FILE *pf;
    pf = fopen(filename, "r");
    if (pf == NULL)return 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; j++)
            fscanf(pf, "%d", a[i] + j);
    }
    fclose(pf);
    return 1;
}

int multiplicaMatriz(int n, int a[n][n], int b[n][n], int result[n][n]) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            result[y][x] = 0;
            for (int i = 0; i < n; i++) {
                result[y][x] += a[y][i] * b[i][x];
            }
        }
    }
    return 1;
}

int produtoEscalar(int vetor_U[], int vetor_V[]) {
    int resultado = 0;
    for (int i = 0; i < VECTOR_SIZE_TO_SHOW; i++) {
        resultado += vetor_U[i] * vetor_V[i];
    }
    return resultado;
}

int multiplicaMatrizThread(int n, int matrixA[n][n], int matrixB[n][n], int result[n][n], int numThread) {
    omp_set_num_threads(numThread);
#pragma omp parallel for
    for (int linha = 0; linha < n; linha++) {
        for (int coluna = 0; coluna < n; coluna++) {
            result[linha][coluna] = 0;
            for (int i = 0; i < n; i++) {
                result[linha][coluna] += matrixA[linha][i] * matrixB[i][coluna];
            }
        }
    }
    return 1;
}

int produtoEscalarThread(int vetor_U[], int vetor_V[], int numThreads) {
    int resultado = 0;
    int nthreads, i, id, nthrds;

#pragma omp parallel num_threads(numThreads)
    {
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
#pragma omp for
        for (i = id; i < 100; i += nthrds) {
            resultado += vetor_U[i] * vetor_V[i];
        }
    }
    return resultado;
}

void printMatrix(int n, int matrix[n][n]) {
    printf("\n   ");
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++)
            printf("%3d  ", matrix[y][x]);
        printf("\n   ");
    }
}

void printVetor(int vetorX[]) {
    for (int i = 0; i < VECTOR_SIZE_TO_SHOW; i++) {
        printf("%d ", vetorX[i]);
    }
}

//Exs functions
double ex1_etapa1(int n, bool isToPrint) {
    double begin, end;
    int matrixA[n][n];
    int matrixB[n][n];
    int matrixC[n][n]; //Resultado
    genRandomMatrix(n, matrixA);
    genRandomMatrix(n, matrixB);
    begin = omp_get_wtime();
    multiplicaMatriz(n, matrixA, matrixB, matrixC);
    end = omp_get_wtime();
    if (isToPrint == TRUE) {
        printf("\n\nEtapa 1:");
        printf("\n • Matriz A:");
        printMatrix(n, matrixA);
        printf("\n • Matriz B:");
        printMatrix(n, matrixB);
        printf("\n • A X B:");
        printMatrix(n, matrixC);
        printf("\n Tempo gasto: %lf segundos", (double) (end - begin));
    }
    return (double) (end - begin);
}

void ex1_etapa2() {
    printf("\n\nEtapa 2:");
    printf(" O esforco computacional é: O(X²), por ser 1 loop dentro de outro que vão de 0 até x!\n");
    printf(" O tempo para calcular a multiplicação de 2 matrizes de tamanho 800 é: ");
    printf("%lf segundos", (double) ex1_etapa1(800, FALSE));
}

double ex1_etapa3(int n, int numThread, bool isToPrint) {
    double begin, end;
    int matrixA[n][n];
    int matrixB[n][n];
    int matrixC[n][n]; //Resultado
    genRandomMatrix(n, matrixA);
    genRandomMatrix(n, matrixB);
    begin = omp_get_wtime();
    multiplicaMatrizThread(n, matrixA, matrixB, matrixC, numThread);
    end = omp_get_wtime();
    if (isToPrint == TRUE) {
        printf("\n\nEtapa 3:");
        printf("\n • Matriz A:");
        printMatrix(n, matrixA);
        printf("\n • Matriz B:");
        printMatrix(n, matrixB);
        printf("\n • A X B:");
        printMatrix(n, matrixC);
        printf("\n Tempo gasto: %lf segundos", end - begin);
    }
    return end - begin;
}

void ex1_etapa4() {
    printf("\n\nEtapa 4:");
    printf("\n O tempo para calcular a multiplicação de matrizes de tamanho de 800 com:");
    printf("\n • 2 threads é: ");
    printf("%lf segundos", ex1_etapa3(800, 2, FALSE));
    printf("\n • 4 threads é: ");
    printf("%lf segundos", ex1_etapa3(800, 4, FALSE));
    printf("\n • 9 threads é: ");
    printf("%lf segundos", ex1_etapa3(800, 9, FALSE));
}

void ex1_etapa5() {
    double seq = ex1_etapa1(800, FALSE);
    double paral = ex1_etapa3(800, 4, FALSE);
    printf("\n\nEtapa 5:");
    printf("\n O tempo do sequêncial: %lf", seq);
    printf("\n O tempo paralelo: %lf", paral);
    printf("\n A latência do speed up (sequêncial/paralelo) é: ");
    printf("%lf \n", (seq / paral));
    printf(" O throughput do speed up (paralelo/sequêncial) é: ");
    printf("%lf \n", (paral / seq));
}

double ex2_etapa1(int n, bool isToPrint) {
    double begin, end;
    int vetor_U[n], vetor_V[n];
    genRandomVector(n, vetor_U);
    genRandomVector(n, vetor_V);
    int resultado;

    begin = omp_get_wtime();
    resultado = produtoEscalar(vetor_U, vetor_V);
    end = omp_get_wtime();

    if (isToPrint == TRUE) {
        printf("\n\nEtapa 1:");
        printf("\n • Vetor_U: ");
        printVetor(vetor_U);
        printf("\n • Vetor_V: ");
        printVetor(vetor_V);
        printf("\n • Produto Escalar: %d\n", resultado);
        printf("\n Tempo gasto: %lf segundos", (double) (end - begin));
    }
    return (double) ((end - begin) / CLOCKS_PER_SEC);
}

void ex2_etapa2() {
    printf("\n\nEtapa 2:");
    printf("\n Complexidade do algoritmo implementado: O(X), por ser apenas 1 loop de 0 até x! ");
    printf("\n O tempo para calcular o produto escalar de 2 vetores de tamanho 100 é: ");
    printf("%lf segundos", ex2_etapa1(100, FALSE));
}

double ex2_etapa3(int n, int numTreads, bool isToPrint) {
    double begin, end;
    int vetor_U[n], vetor_V[n];
    genRandomVector(n, vetor_U);
    genRandomVector(n, vetor_V);
    int resultado = 0;

    begin = omp_get_wtime();
    resultado = produtoEscalarThread(vetor_U, vetor_V, numTreads);
    end = omp_get_wtime();

    if (isToPrint == TRUE) {
        printf("\n\nEtapa 3:");
        printf("\n • Vetor_U: ");
        printVetor(vetor_U);
        printf("\n • Vetor_V: ");
        printVetor(vetor_V);
        printf("\n • Produto Escalar: %d\n", resultado);
        printf("\n Tempo gasto: %lf segundos", end - begin);
    }

    return end - begin;
}

void ex2_etapa4() {
    printf("\n\nEtapa 4:");
    printf("\n O tempo para calcular o produto escalar de vetor de tamanho de 100 com:");
    printf("\n • 2 threads é: ");
    printf("%lf segundos", ex2_etapa3(100, 2, FALSE));
    printf("\n • 4 threads é: ");
    printf("%lf segundos", ex2_etapa3(100, 4, FALSE));
    printf("\n • 8 threads é: ");
    printf("%lf segundos", ex2_etapa3(100, 8, FALSE));
}

void ex2_etapa5() {
    double seq = ex2_etapa1(100, FALSE);
    double paral = ex2_etapa3(100, 4, FALSE);
    printf("\n\nEtapa 5:");
    printf("\n O tempo do sequêncial: %lf", seq);
    printf("\n O tempo paralelo: %lf", paral);
    printf("\n A latência do speed up (sequêncial/paralelo) é: ");
    printf("%lf \n", (seq / paral));
    printf(" O throughput do speed up (paralelo/sequêncial) é: ");
    printf("%lf \n", (paral / seq));
}



