#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int thread_num = 8;
int ops_num = 7;

int var = 0;

void *tadd(void* arg) {
	for (int i = 0; i < ops_num; i++) {
		var++;
	}

	return NULL;
}

void *tsub(void* arg) {
	for (int i = 0; i < ops_num; i++) {
		var--;
	}

	return NULL;
}

void operate() {
	pthread_t *adders = malloc(thread_num * sizeof(pthread_t));
	pthread_t *subbers = malloc(thread_num * sizeof(pthread_t));

	for(int i = 0; i < thread_num; i++) {
		pthread_create(&adders[i], NULL, &tadd, NULL);
		pthread_create(&subbers[i], NULL, &tsub, NULL);
	}

	for (int i = 0; i < thread_num; i++) {
		pthread_join(adders[i], NULL);
		pthread_join(subbers[i], NULL);
	}
	
	printf("var = %d\n", var);
}

int main(int argc, char** argv) {
	for (int i = 0; i < 10; i++) {
		operate();
	}
}

