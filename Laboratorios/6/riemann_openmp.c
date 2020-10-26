#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

typedef struct timespec walltime_t;

void walltime_start(walltime_t* start){
    clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;

    return elapsed;
}
/* @brief definicion de la funcion que establece la curva
    @param valor de x a ser evaluado en la funcion
    @return resultado y al evaluar x en la funcion X² + 1 */
double function(double x){
    return (x * x) + 1; // X² + 1
}


/* @brief Calcular la aproximación al area bajo la curva de la función dada
    @param a limite inferior del area
    @param b limite superior del area
    @param n cantidad de rectangulos
    @param thread_count cantidad de hilos
    @return aproximación del area bajo la curva*/
double riemann_sum(size_t a, size_t b, size_t n, size_t thread_count){
    double delta = (b - a) / (double)n;
    double result = 0.0;
    double rectangle_height = 0.0;

    #pragma omp parallel for num_threads(thread_count) default(none) shared(delta, a,b,n) private(rectangle_height) reduction(+:result)
    for (size_t i = 0; i < n; ++i){
        if (i * delta + a <= b){
            rectangle_height = function( (i * delta) + 1);
            result += delta * rectangle_height;
        }
    }

    return result;
}


int main(int argc, char * arg[]){
    walltime_t* walltime = (walltime_t*)calloc(1, sizeof (walltime_t));

    size_t a = 0;
    size_t b = 0;
    size_t n = 0;
    size_t thread_count = 0;
    double result = 0.0;
    if (argc > 4){
        a = (size_t)strtoul(arg[1], NULL, 10);
        b = (size_t)strtoul(arg[2], NULL, 10);
        n = (size_t)strtoul(arg[3], NULL, 10);
        thread_count = (size_t)strtoul(arg[4], NULL, 10);
    }
    else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }
    walltime_start(walltime);
    
    result = riemann_sum(a,b,n,thread_count);

    double execution_time = walltime_elapsed(walltime);

    printf("The estimated area is: %0.2f\nThe expended time was: %f\n", result, execution_time);

    return 0;
}