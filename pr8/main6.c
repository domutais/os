#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int delay = 5;

void byebye(void* arg) {
	fprintf(stderr, "Bye bye! Thread was terminated while at iteration %d\n", *(int*)arg);
}

void* tThread(void *arg) {
	int i = 0;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	pthread_cleanup_push(&byebye, &i);

	while(1) {
		printf("Child thread. Iteration %d\n", i);
		sleep(1);
		i++;	
	}

	pthread_cleanup_pop(1);
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
