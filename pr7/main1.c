#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SLEEP_TIME 2

void* threadA(void* arg) {
	for (int i = 0; i < 10; i++) {
		printf("Child thread. Iteration: %d\n", i);
		sleep(SLEEP_TIME);
	}

	return 0;
}

int main(void) {
	pthread_t thread;
	if (pthread_create(&thread, NULL, &threadA, NULL) != 0) fprintf(stderr, "Failed to start thread\n");

	for (int i = 0; i < 10; i++) {
		printf("Parent thread. Iteration %d\n", i);
		sleep(SLEEP_TIME);
	}

	return 0;
}
