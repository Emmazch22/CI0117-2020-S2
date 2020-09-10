#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BILLION 1000000000L

/* Función vacia ejecutada por el hilo secundario 
    @param {void *} args (no se utiliza)
    @return {NULL}*/
void * time_test(void * args){
    return NULL;
}

/* Determinar el tiempo minimo en un arreglo
    @param  {double *} times_array - arreglo de tiempos
    @param {size_t} test_num - cantidad de pruebas realizadas (tamaño del arreglo)
    @return {double} menor tiempo en el arreglo */
double min_Time(double * times_array, size_t test_num){
    double min_time = times_array[0];
    for (size_t j = 0; j < test_num; j++){
        if (times_array[j] < min_time){
            min_time = times_array[j];
        }
    }
    return min_time;
}

/* Método main
    @param {int} argc - contador de argumentos
    @param {char *} arg[] - arreglo de argumentos */
int main (int argc, char * arg[]){
    pthread_t thread;
    size_t test_num = 0;
    struct timespec start, finish;
    double time = 0.0;

    //Validar cantidad de argumentos ingresados
    if (argc >= 2){
        test_num = (size_t)strtoul(arg[1], NULL, 10);
    }
    else {
        //Si no se especifican argumentos se asume que test_num = 1
        test_num = 1;
    }
    //Arreglo donde se almacenan los tiempos
    double times_array[test_num];

    //Creación del hilo secundario y ejecución de test_num cantidad de pruebas
    for (size_t i = 0; i < test_num; ++i){
        //Tiempo inicial
        clock_gettime(CLOCK_REALTIME, &start);
        pthread_create(&thread, NULL,  time_test, (void*) i);
        //Tiempo final
        clock_gettime(CLOCK_REALTIME, &finish);
        //Establecer valor del tiempo de creación y destrucción
        time = (double) ((finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / (double) BILLION);
        //Almacenar los tiempos en el arreglo de tiempos
        times_array[i] = time;
    }

    printf("Minimun thread creation and destruction time was %fs among %zu trials\n", min_Time(times_array, test_num), test_num);

    for (size_t i = 0; i < test_num; ++i){
        pthread_join(thread, NULL);
    }

    return 0;
}
