#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void printArray(int array[], int count);

int main(int argc, char *argv[]){
    int rank, nproc;
    

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int * array;
    int size;

    if (rank == 0){
        std::cout << "Introduzca un numero multiplo de " << nproc << ": ";
        std::cin >> size;
        if (size % nproc != 0){
            MPI_Finalize();
            exit(0);
        }
        array = new int[size];
        for(int i = 0; i < size; i++){
            array[i] = i;
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    int s_trozo = size / nproc;
    int * trozo = new int[s_trozo];
    for(int i = 0; i < s_trozo; i++){
        int calc = (s_trozo * rank) + i;
        trozo[i] = array[calc];
    }
    printArray(trozo, size);
    /*
    int s_trozo = size / nproc;
    int * trozo = new int[s_trozo];
    int calc = (s_trozo * rank);
    int * pointer;
    pointer = array;
    //MPI_Scatter(&(*(array+calc)), 2, MPI_INT, &trozo, 2, MPI_INT, 0, MPI_COMM_WORLD);
    std::cout<<trozo[0] <<" " <<trozo[1];
    */
    MPI_Finalize();
    return 0;
}

void printArray(int array[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
}
