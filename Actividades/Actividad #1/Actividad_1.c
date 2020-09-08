#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void * thread_race(void * args, size_t threads){
	thread_mutex_lock(&mutex);
	size_t thread_num = (size_t) args;
	printf("Thread %zu/%zu: I arrived at position %zu ", thread_num, threads, threads+1);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main (int argc, char * arg[]){

	size_t thread_count = 0;
	pthread_mutex_init(&mutex, NULL);
	if (argc >= 2){
		thread_count = (size_t)strtoul(arg[1], NULL, 10);
	}
	else {
		fprintf(stderr, "Error, invalid number of parameters\n");
		return 1;
	}

	pthread_t * threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

	for (size_t i = 0; i < thread_count; ++i){
		pthread_create(&threads[i], NULL, thread_race, (void *)threads[i], thread_count);
	}

	for (size_t i = 0; i < thread_count; ++i){
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	free(threads);


	return 0;
}
