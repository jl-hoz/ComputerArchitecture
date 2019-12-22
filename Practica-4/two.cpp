#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char **argv ){
    int rank, size;
    int * send, * recv;
    

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    
    send = (int *) malloc(size * sizeof(int));
    recv = (int *) malloc(size * sizeof(int));

    // INITIALIZE MATRIX (ARRAY FOR EACH PROCESS)
    for (int i=0; i < size ; i++)
        send[i] = (i+1) + rank*size;

    // PRINT SEND
    printf("\nProcess %d: send -> ", rank);
    for(int i = 0; i < size; i++){
        printf("%d ", send[i]);
    }

    MPI_Alltoall(&send, 1, MPI_FLOAT, &recv, 1, MPI_INT, MPI_COMM_WORLD);

    // PRINT RECEIVE
    printf("\nProcess %d: receive -> ", rank);
    for(int i = 0; i < size; i++){
        printf("%d ", recv[i]);
    }

    MPI_Finalize();

    return 0;
}