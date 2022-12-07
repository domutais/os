#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_RANDOM 200


double f(double x) { return 4 - x*x; }

typedef struct arg {
	int *arr;
	int len;
} arg_t;

double result = 0.0;

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
void* tread(void *arg) {
	arg_t array = *(arg_t*)arg;
	
	int amount = rand() % (array.len-1) + 1;
	
	while(1) {
	pthread_rwlock_rdlock(&lock);
	printf("Reader %d read element(s): ", pthread_self());
	for (int i = 0; i < amount; i++) {
		printf("%d ", array.arr[rand() % array.len]);
	}
	printf("\n");
	pthread_rwlock_unlock(&lock);
	sleep(0.7);
	}

	return NULL;
}

void* twrite(void *arg) {
	arg_t array = *(arg_t*)arg;

	int amount = rand() % (array.len-1) + 1;
	
	while(1) {
	pthread_rwlock_wrlock(&lock);
	printf("Writer %d wrote element(s): ", pthread_self());
	for (int i = 0; i < amount; i++) {
		int a = rand() % MAX_RANDOM;
		printf("%d ", a);
		array.arr[rand() % array.len] = a;
	}
	printf("\n");
	pthread_rwlock_unlock(&lock);
	sleep(1);
	}
	

	return NULL;
}

void* tprint(void* arg) {
	arg_t array = *(arg_t*)arg;
	while(1) {
		pthread_rwlock_rdlock(&lock);
		printf("[ ");
		for (int i = 0; i < array.len; i++) {
			printf("%d ", array.arr[i]);
		}	
		printf("]\n");
		pthread_rwlock_unlock(&lock);
		
		sleep(1.5);
		
	}
	return NULL;
}

int main(int argc, char** argv) {
	int arr_len = 15;
	if (argc > 1) arr_len = atoi(argv[1]);

	int writers = 3;
	if (argc > 2) writers = atoi(argv[2]);

	int readers = 5;
	if (argc > 3) readers = atoi(argv[3]);

	int *arr = malloc(arr_len*sizeof(int));
	
	pthread_t *wr_arr = malloc(writers*sizeof(pthread_t));
	pthread_t *rd_arr = malloc(readers*sizeof(pthread_t));
	pthread_t printer;
	
	arg_t a = (arg_t){arr, arr_len};

	for(int i = 0; i < writers; i++) {
		pthread_create(&wr_arr[i], NULL, &twrite, &a);
	}

	for(int i = 0; i < readers; i++) {
		pthread_create(&rd_arr[i], NULL, &tread, &a);
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&printer, &attr, &tprint, &a);

	sleep(writers + readers + 1);

	for (int i = 0; i < writers; i++) {
		pthread_cancel(wr_arr[i]);
	}
	for (int i = 0; i < readers; i++) {
		pthread_cancel(rd_arr[i]);
	}
}



