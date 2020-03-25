#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
        int size, rank, dest, source, count, tag=1;
        int inmsg, outmsg=1;
        MPI_Status Stat;

        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 0) {
          dest = 1;
          source = 1;
          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
          printf("Mensaje recibido por el proceso %d: %d\n", rank, inmsg);

        }else if (rank == 1) {
          dest = 0;
          source = 0;
          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
          printf("Mensaje recibido por el proceso %d: %d\n", rank, inmsg);
         }

        MPI_Finalize();
}

