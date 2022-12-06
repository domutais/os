#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int *workArr = NULL;
int threads_num;

void *tCalculate(void *arg) {
	unsigned long long id = ((unsigned long long)arg - (unsigned long long)workArr)/sizeof(int);
	printf("Thread %lld: started.\n", id);
	sleep(id);
	
	int ret = rand() % 10 + 1;
	printf("Thread %lld: generated number %d.\n", id, ret);

	*(int*)(arg) = ret;

	return NULL;
}

void *tPrinter(void *arg) {
	int elements = 0;

	while(elements < threads_num) {
		elements = 0;
		
		printf("[ ");
		for (int i = 0; i < threads_num; i++) {
			printf("%d ", workArr[i]);
			if (workArr[i]) elements++;
		}
		printf("]\n");

		sleep(1);
	}
}


void createThreads(pthread_t **arr) {
	for (int i = 0; i < threads_num; i++) {
		pthread_create(arr[i], NULL, &tCalculate, &workArr[i]);
		printf("Thread creator: created thread %d.\n", i);
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));

	if (argc > 1) threads_num = atoi(argv[1]);
	else threads_num = 10;

	pthread_t **threads = malloc(threads_num * sizeof(pthread_t*));
	for (int i = 0; i < threads_num; i++) {
		threads[i] = malloc(sizeof(pthread_t));
	}
	
	workArr = calloc(threads_num, sizeof(int));
	createThreads(threads);

	pthread_t printer;
	pthread_create(&printer, NULL, &tPrinter, NULL);

	pthread_join(printer, NULL);

	return 0;
		
}
