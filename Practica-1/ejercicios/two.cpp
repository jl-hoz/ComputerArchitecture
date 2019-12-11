#include <mpi.h>
#include <iostream>

int main(int argc, char **argv){
  int rank, nproc;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int read, data;

  // Father send data
  if (rank == 0){
    std::cout << "Introduzca un numero entero: ";
    std::cin >> read;
    printf("\nParent process with rank %d send %d\n", rank, read);
    MPI_Send(&read, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
  }
  // Son receive data and send it to another son.
  else{
    MPI_Recv(&data, 1, MPI_INT, (rank - 1), 100, MPI_COMM_WORLD, &status);
    printf("\nProcess with rank %d receive %d\n", rank, data);
    data++;
    // Last son do not send data
    if (rank < nproc - 1){
      MPI_Send(&data, 1, MPI_INT, (rank + 1), 100, MPI_COMM_WORLD);
      printf("Process with rank %d send %d\n", rank, data);
    }
  }

  MPI_Finalize();
  return 0;
}
