#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, count;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0){
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Send(a, 10000, MPI_FLOAT, 1, 100, MPI_COMM_WORLD);
        MPI_Recv(b, 10000, MPI_FLOAT, 1, 100, MPI_COMM_WORLD, &status);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[300]);
    }else{
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Recv(b, 10000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &count);
        MPI_Send(a, 10000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD);
        printf("Process %d:\nValue from random index of array B: %lf\n\n", rank, b[200]);
    }
    MPI_Finalize();
    return 0;
}