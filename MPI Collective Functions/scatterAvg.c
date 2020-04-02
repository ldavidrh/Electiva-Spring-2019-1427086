#include "mpi.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define ELEMENTS_PER_PROC 5

float calcularPromedio(float *array, int num_elementos);
float *generarVectorAleatorio(int num_elementos);

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    char hostname[HOST_NAME_MAX + 1];
    MPI_Status Stat;
    srand(time(NULL));
    gethostname(hostname, HOST_NAME_MAX + 1);

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    float *rand_vect = NULL;
    if (myrank == 0) //Si soy el proceso root, genero el arreglo de numeros aleatorios
    {
        rand_vect = generarVectorAleatorio(ELEMENTS_PER_PROC * worldsize);
    }

    //Creo un arreglo de numeros que contendra el subconjunto de datos del arreglo aleatorio 
    //que los procesos van a recibir
    float *sub_rand_vect = (float *)malloc(sizeof(float) * ELEMENTS_PER_PROC);

    //Dispersamos el arreglo entre todos los procesos
    MPI_Scatter(rand_vect, ELEMENTS_PER_PROC, MPI_FLOAT, sub_rand_vect,
                ELEMENTS_PER_PROC, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //Calculamos el promedio de cada subconjunto de datos del vector original
    float sub_vector_avg = calcularPromedio(sub_rand_vect, ELEMENTS_PER_PROC);

    //Si soy el proceso root creo un vector que recibira los promedios parciales de cada proceso
    //y luego recolecto los promedios de cada proceso
    float *sub_avgs = NULL;
    if (myrank == 0)
    {
        sub_avgs = (float *)malloc(sizeof(float) * worldsize);
    }
    MPI_Gather(&sub_vector_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0,
               MPI_COMM_WORLD);

    //Calcular el promedio de los promedios calculados por cada proceso.
    if (myrank == 0)
    {
        float avg = calcularPromedio(sub_avgs, worldsize);
        printf("El promedio calculado con los procesos es %.6f\n", avg);

        float localavg = calcularPromedio(rand_vect, ELEMENTS_PER_PROC * worldsize);
        printf("El promedio calculado directamente es %.6f\n", localavg);
    }

    if (myrank == 0)
    {
        free(rand_vect);
        free(sub_avgs);
    }

    free(sub_rand_vect);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}


float calcularPromedio(float *array, int num_elementos)
{
    float sum = 0.f;
    for (int i = 0; i < num_elementos; i++)
    {
        sum += array[i];
    }
    return sum / num_elementos;
}

float *generarVectorAleatorio(int num_elementos)
{
    float *rand_vect = (float *)malloc(sizeof(float) * num_elementos);
    //assert(rand_vect != NULL); //Asegura de que el vector no sea NULL, en caso de serlo el programa se finaliza

    for (int i = 0; i < num_elementos; i++)
    {
        rand_vect[i] = (rand() % 50);
    }
    return rand_vect;
}