#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, nproc, count;
    
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    
    if(rank == 0){
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Send(a, 10000, MPI_FLOAT, 1, 100, MPI_COMM_WORLD);
        printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], (rank+1));
        MPI_Recv(b, 10000, MPI_FLOAT, (nproc - 1), 100, MPI_COMM_WORLD, &status);
        printf("Process %d:\n Receive %lf from process %d\n\n", rank, b[300], (nproc - 1));
    }else{
        float a[10000], b[10000];
        for(int i = 0; i < 10000; i++){
            a[i] = rank;
        }
        MPI_Recv(b, 10000, MPI_FLOAT, (rank - 1), 100, MPI_COMM_WORLD, &status);
        printf("Process %d:\n Receive %lf from process %d\n\n", rank, b[300], (rank - 1));
        MPI_Get_count(&status, MPI_CHAR, &count);
        if(rank == (nproc - 1)){ // Tail
            MPI_Send(a, 10000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD);
            printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], 0);
        }else{
            MPI_Send(a, 10000, MPI_FLOAT, (rank + 1), 100, MPI_COMM_WORLD);
            printf("Process %d:\n Send %lf to process %d\n\n", rank, a[300], (rank+1));
        }
    }
    MPI_Finalize();
    return 0;
}