#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector(v, n) printf("Mi vista (%d) del vector\n", myrank); for (i = 0; i < n; i++) printf("[%d: %d] ", myrank, v[i]); printf("\n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i;
    int root;
    int vector[MAXVECT];
    int *rec_vector;
    char hostname[HOST_NAME_MAX + 1];

    gethostname(hostname, HOST_NAME_MAX + 1);
    srand(time(NULL));
    int choosen = (rand() % MAXPROC);
    rec_vector = (int *)malloc(sizeof(int) * MAXVECT / worldsize);
    root = 0;
    // Escriba las lineas que permitan:
    //  (1) Inicializar el dominio MPI
    //  (2) Guardar en la variable 'worldsize' el numero de procesos
    // involucrados en la ejecucion de esta app
    //  (3) Guardar el rango del proceso
    //
    // (1)

    // (2)

    // (3)

    if (myrank == choosen)
    {
        imprimirvector(vector, MAXVECT);
    }
    if (myrank == 0)
    { // proceso con rango 0 inicializara el vector
        for (i = 0; i < MAXVECT; i++)
            vector[i] = i;
    }
    // Escriba la linea que permite distribuir el vector con la instruccion
    // MPI_Scatter. Use la variable 'rec_vector' para recibir los datos.
    //
    // (4)

    //First we need to know if the size of the array is divisible by the number of process(world_size)
    int vector_size = sizeof(vector)/sizeof(vector[0]);
    int sendcnt;
    if(vector_size % worldsize == 0){
        sendcnt = vector_size/worldsize;
    }else{
        sendcnt = floor(vector_size/worldsize);
        remainingValues = vector_size % worldsize; 
    }

    if(myrank == 0){

    }
    //
    if (myrank == choosen)
    {
        imprimirvector(rec_vector, MAXVECT / MAXPROC);
    }
    // Inserta la instruccion que termina el contexto de ejecucion de MPI
    //
    // (5)

    return 0;
}