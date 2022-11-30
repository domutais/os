#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define SLEEP_TIME 0.02

#define STOP 7
#define MAX_NUM 24 // must be (STOP+1) or greater
#define NUMBERS_AMOUNT 25
#define STRINGS_AMOUNT 40

void* threadPrinter(void* arg) {
	for (int i = 0; i < STRINGS_AMOUNT; i++) {
		int num = *(int*)arg;
		if (num != STOP) printf("Child thread. Iteration: %d (received %d)\n", i, num);
		else {
			fprintf(stderr, "Recieved %d. Stopping printer.\n", STOP);
			break;
		}
		sleep(SLEEP_TIME);
	}

	return 0;
}

void* threadGenerator(void* arg) {
	srand(time(NULL));
	for (int i = 0; i < NUMBERS_AMOUNT; i++) {
		int num = rand() % MAX_NUM;
		//printf("Generator: generated %d\n", num);
		*(int*)arg = num;
		sleep(SLEEP_TIME);
	}

	return NULL;
}

int main(void) {
	pthread_t printer, generator;
	int num;
	
	if (pthread_create(&printer, NULL, &threadPrinter, &num) != 0) fprintf(stderr, "Failed to start printer\n");
	if (pthread_create(&generator, NULL, &threadGenerator, &num) != 0) fprintf(stderr, "Failed to start generator.\n");
	
	if (pthread_join(generator, NULL) != 0) fprintf(stderr, "Failed to join generator\n");
	else printf(" Joined generator.\n");

	if (pthread_join(printer, NULL) != 0) fprintf(stderr, "Failde to join printer\n");
	else printf (" Joined printer.\n");

	printf("Work finished.\n");

	return 0;
}
