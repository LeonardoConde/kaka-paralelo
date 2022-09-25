#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct ContaCorrente {
   int numero;
   char cliente[80];
   float saldo;
} tipo_conta;

void *depositar(void *cc);
void *retirar(void  *cc);
void iniciarSaldo (tipo_conta *cc);
void mostrarCC (tipo_conta cc);


int main()
{
      int fim = FALSE;
      tipo_conta conta1;
      pthread_t thread1,thread2;
      int tentativas = 0;

      strcpy(conta1.cliente,"Joao da Sila");
      conta1.numero = 1234;
      conta1.saldo = 0.0;
      mostrarCC(conta1);
      while (!fim) {
          iniciarSaldo(&conta1); // inicia saldo com 5000
          // threads que realizam as operações na mesma conta corrente
          pthread_create(&thread1, NULL, depositar,&conta1); // operação de deposito (R$300,00)
          pthread_create(&thread2, NULL, retirar,&conta1); // operação de retirada (R$500,00)
          pthread_join(thread1,NULL);
          pthread_join(thread2,NULL);
          tentativas++;

          if (conta1.saldo != 4800) fim = TRUE;
            else mostrarCC(conta1);
      }
      printf("Saldo inconsistente na tentativa %d!!!\n",tentativas);
      mostrarCC(conta1);
    exit(0);
}

void iniciarSaldo (tipo_conta *cc) {
      cc->saldo = 5000;
}

void mostrarCC (tipo_conta cc) {
      printf("-----------------------------------------------------------------------------------\n");
      printf("Nome: %s\n",cc.cliente);
      printf("Conta corrente: %d\n",cc.numero);
      printf("Saldo da conta: %f\n",cc.saldo);
      printf("-----------------------------------------------------------------------------------\n");
}

void *depositar(void *cc) {
       float saldo_conta;
       
       saldo_conta = ((tipo_conta *) cc)->saldo;
       saldo_conta = saldo_conta+300;
       ((tipo_conta *) cc)->saldo = saldo_conta;
}


void *retirar(void *cc) {

       float saldo_conta;

       saldo_conta = ((tipo_conta *) cc)->saldo;
       saldo_conta = saldo_conta - 500;
       ((tipo_conta *) cc)->saldo = saldo_conta;

}





