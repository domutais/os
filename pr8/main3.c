#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int delay = 5;

void* tThread(void *arg) {
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	for(int i = 0; i < delay*2; i++) {
		printf("Child thread. Iteration %d\n", i);
		sleep(1);	
	}

	return NULL;
}

int main(int argc, char** argv) {
	if (argc > 1) delay = atoi(argv[1]);

	pthread_t thread;
	pthread_create(&thread, NULL, &tThread, NULL);

	sleep(delay);	

	int result;

	pthread_cancel(thread);
	printf("Tried to cancel thread...\n");

	pthread_join(thread, &result);
	printf("Thread finished (%s)\n", result == PTHREAD_CANCELED ? "canceled" : "exited");

	return 0;
}
