#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct params {
	char* name;
	char* str;
	int num;
} params_t;

void* func(void* arg) {
	params_t par = *((params_t*) arg);

	for (int i = 0; i < par.num; i++) {
		printf("Thread %s. %s %d\n", par.name, par.str, i);
	}

	return NULL;
}

int main(void) {
	pthread_t threads[4];

	char* names[] = {"Alice", "Bob", "Charlie", "David"};
	char* strs[] = {"Yo", "Sup", "Hello", "Hi"};
	int nums[] = {3, 5, 6, 4};

	params_t pars[4];
	for (int i = 0; i < 4; i++) {
		pars[i] = (params_t){names[i], strs[i], nums[i]};
		if (pthread_create(&threads[i], NULL, &func, &pars[i]) != 0) fprintf(stderr, "Failed to start thread %d", i);
	}

	while(1);
	return 0;
}
