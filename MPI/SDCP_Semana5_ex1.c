#include "mpi.h"
#include <stdio.h>
#include <string.h>

/*
 * Integrantes:
 *  - Leonardo de Jesus Diz Conde
 *  - Lucas Kenji Uezu
 *  - Victor Yuji Saito
 */

int main(int argc, char **argv){
    int rank,size,tag,i;
    MPI_Status status;
    char msg[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0) {
        strcpy(msg,"12345");
        for(i=1;i<size;i++)
            MPI_Send(msg,5,MPI_CHAR,i,tag,MPI_COMM_WORLD);
    } else {
        MPI_Recv(msg,5,MPI_CHAR,0,tag,MPI_COMM_WORLD, &status);
        printf("Message received: %s\n",msg);
    }
    MPI_Finalize();

    return 0;
}