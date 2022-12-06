#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int delay = 5;

void* tThread(void *arg) {
	double *pi_4 = (double*)arg;
	
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	for (int i = 0; i < 100000; i++) {
		double next = 1.0/(2*i+1);
		
		if (i % 2 == 1) next = -next;

		*pi_4 += next;
		
		printf("Thread: pi = %lf [%d]\n", (*pi_4) * 4, i);
		pthread_testcancel();		

	}

	return NULL;
}

int main(int argc, char** argv) {
	if (argc > 1) delay = atoi(argv[1]);

	pthread_t thread;

	double pi_4;
	pthread_create(&thread, NULL, &tThread, &pi_4);

	sleep(delay);	

	int result;

	pthread_cancel(thread);
	printf("Tried to cancel thread...\n");

	pthread_join(thread, &result);
	printf("Thread finished (%s)\n", result == PTHREAD_CANCELED ? "canceled" : "exited");
	if (result) printf("THREAD FINISHED: pi = %lf\n", pi_4 * 4);

	return 0;
}
