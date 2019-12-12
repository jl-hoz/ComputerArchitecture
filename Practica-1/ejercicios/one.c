#include <mpi.h>
#include <stdio.h>


int main(int argc, char** argv){
    int nproc, myrank;
    double start, finish, time;
    FILE *fp;

    fp = fopen("./test.txt","a");

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    printf("Hola mundo, soy el proceso %d de un total %d.\n", myrank, nproc);
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    time = finish - start;
    printf("Total time of %d: %f\n", myrank, time);

    if(fp == NULL){
        printf("Error!");               
    }
    else{
        fprintf(fp,"%lf;",time);
        fclose(fp);
    }

    MPI_Finalize();

    return 0;
}
