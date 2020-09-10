#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

/* Definición de estructuras */
typedef struct {
    sem_t * semaphores_array;
} shared_data_t;

typedef struct {
    size_t thread_num;
    shared_data_t * shared_data;
} thread_data_t;

void * helloWorld(void * args){

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_data_t* shared_data = data->shared_data;
    /* Semaforo en espera */
    sem_wait(&shared_data->semaphores_array[thread_num]);

    printf("Hello World from thread number # %zu\n", thread_num);
    /* Liberar semaforo */
    sem_post(&shared_data->semaphores_array[thread_num]);

    return NULL;
}

int main(int argc, char * arg[]) {
    size_t thread_count = 0;
    double execution_time = 0.0;

    clock_t begin = clock();
    /* Validación de parametros */
    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }
    /* Arreglos de datos con alojamiento en la memoria */
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));    
    
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    sem_t * semaphores = malloc((size_t)(thread_count * sizeof(sem_t)));

    /* Inicialización de los semaforos */
    for (size_t i = 0; i < thread_count; ++i){
        sem_init(&semaphores[i], 0, thread_count);
    }
    /* Asignación de datos a shared_data y creación de hilos */
    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        thread_data_list[i].shared_data->semaphores_array = semaphores;
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
    }    
    /* Pthread_join para cada hilo del arreglo */
    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }
    /* Destrucción de los semeforos en el arreglo de shared_data */
    for (size_t i = 0; i < thread_count; ++i) {
        sem_destroy(&thread_data_list->shared_data->semaphores_array[i]);
    }
    clock_t end = clock();
    /* Mostrar tiempo de ejecución */
    execution_time += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nExecution time was %fs\n",execution_time);
    /* Liberación de memoria */
    free(threads);
    free(semaphores);
    free(shared_data);
    free(thread_data_list);

    return 0;    
}