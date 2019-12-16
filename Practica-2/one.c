#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[]){
    int rank, count;
    char msg[20];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int contador = 0;
    int limite = 3;
    do{
        if(rank == 0){
            printf("MASTER SENDING, Message id: %d\n", contador);
            strcpy(msg, "HELLO WORLD!");
            MPI_Send(msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
            if(contador != 0){
                MPI_Recv(msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD, &status);
                printf("MASTER RECEIVE: %s, Message id: %d\n", msg, contador);
            }
        }else{
            MPI_Recv(msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
            printf("_SLAVE RECEIVE: %s, Message id: %d\n", msg, contador);
            MPI_Get_count(&status, MPI_CHAR, &count);
            printf("_SLAVE SENDING, Message id: %d\n", contador);
            strcpy(msg, "Hello World!");
            MPI_Send(msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD);
        }
        contador++;
    }while (contador != limite);
    
    
    MPI_Finalize();
    return 0;
}
