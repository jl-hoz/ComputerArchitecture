#include <mpi.h>
#include <iostream>

int main(int argc, char **argv){
  int rank, nproc;
  int read, data = 0;
  double start, finish, time;

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Father send data
  if (rank == 0){
    std::cout << "Introduzca un numero entero: ";
    std::cin >> read;
  }

  for(int i = 0, id = 0; i < read; i++){
    if(rank == id){
      // If is father and is not first iteration then receive from tail list
      if(i != 0 && rank == 0){
        MPI_Recv(&data, 1, MPI_INT, (nproc - 1), 100, MPI_COMM_WORLD, &status);
        printf("\nProcess with rank %d receive %d\n", rank, data);
      }else if(rank != 0){ // Receive data from rank-1 process
        MPI_Recv(&data, 1, MPI_INT, (rank - 1), 100, MPI_COMM_WORLD, &status);
        printf("\nProcess with rank %d receive %d\n", rank, data);
      }
      
      
      data++; // Increment data

      // Process send data to next process
      if (rank < nproc - 1){
        MPI_Send(&data, 1, MPI_INT, (rank + 1), 100, MPI_COMM_WORLD);
        printf("Process with rank %d send %d\n", rank, data);
      }else{ // Last process send data to first process
        MPI_Send(&data, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
        printf("Last Process with rank %d send %d\n", rank, data);
      }
    }
    id++;
    if(id == nproc - 1){
      id = 0;
    }
  }

  MPI_Finalize();
  return 0;
}
