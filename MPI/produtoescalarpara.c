#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000

#define NTHREADS 8

void iniciarVetor(int vet[]);

int main() {

  int u[N];
  int v[N];
  int uxv=0;
  int i;

  srand(time(NULL));
  
  printf("Tamanho do vetor: %d\n",N);
  iniciarVetor(u);
  iniciarVetor(v);
  
  omp_set_num_threads(NTHREADS);
  double st=omp_get_wtime();
  
  #pragma omp parallel for reduction (+:uxv)
  for(i=0;i<N;i++)
    uxv += u[i]*v[i];
    
  double en=omp_get_wtime();
  printf("Tempo do processamento: %lf\n",en-st);
  printf("produto escalar u.v = %d\n",uxv);
  
  printf("\nCalculo finalizado!\n");


  exit(0);

}

void iniciarVetor(int vet[]) {

   int i;
   
   omp_set_num_threads(NTHREADS);
   #pragma omp parallel for 
   for(i=0;i<N;i++)
      vet[i] = rand()%100;
}
