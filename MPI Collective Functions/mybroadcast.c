#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector                            \
    printf("Mi vista (%d) del vector\n", myrank); \
    for (i = 0; i < MAXVECT; i++)                 \
        printf("[%d: %d] ", myrank, invect[i]);   \
    printf("\n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i;
    int outvect[MAXVECT], invect[MAXVECT];
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status Stat;

    gethostname(hostname, HOST_NAME_MAX + 1);
    srand(time(NULL));
    int choosen = (rand() % MAXPROC);
    // Escriba las lineas que permitan:
    //  (1) Inicializar el dominio MPI
    //  (2) Guardar en la variable 'worldsize' el numero de procesos
    // involucrados en la ejecucion de esta app
    //  (3) Guardar el rango del proceso
    //
    // (1)
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    // (3)
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == choosen)
    {
        imprimirvector
    }
    if (myrank == 0)
    { // proceso con rango 0 inicializara el vector
        for (i = 0; i < MAXVECT; i++)
            outvect[i] = i;
    }
    // Escriba la linea que permite distribuir el vector con las instrucciones MPI_Send y MPI_Recv
    //
    // (4)

    if (myrank == 0)
    {
        for (i = 0; i < worldsize; i++)
        {
            if (myrank != i)
            {
                MPI_Send(&outvect, MAXVECT, MPI_INT, i, 0, MPI_COMM_WORLD);
                //printf("Host: %s, process %d just sent \"%d\" to process %d\n", hostname, myrank, inmsg, i);
            }
        }
    }
    else
    {
        MPI_Recv(&invect, MAXVECT, MPI_INT, 0, 0, MPI_COMM_WORLD, &Stat);
        //printf("Host: %s, process %d just received: %d\n", hostname, myrank, outmsg);
    }

    if (myrank == choosen)
    {
        imprimirvector
    }
    // Inserta la instruccion que termina el contexto de ejecucion de MPI
    //
    // (5)
    MPI_Finalize();
    return 0;
}
