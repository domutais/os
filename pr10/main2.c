#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAIN_DELAY 42
#define PRODUCER_DELAY 8

int buf = 0;

typedef struct cv {
	pthread_mutex_t mut;
	pthread_cond_t cond;
} cond_var;

void cond_wait(cond_var *c) {
	pthread_mutex_lock(&c->mut);
	pthread_cond_wait(&c->cond, &c->mut);
}

void cond_continue(cond_var *c) {
	pthread_mutex_unlock(&c->mut);
}

void* tProducer(void *arg) {
	while(1) {
		buf = rand() % 100 + 1;
		printf("P: Produced %d\n", buf);
		pthread_cond_signal(&((cond_var*)arg)->cond);
		sleep(PRODUCER_DELAY);
	}

	return NULL;
}

void* tConsumer(void *arg) {
	while(1) {
		printf("R: Ready to recieve\n");
		cond_wait((cond_var*)arg);
		printf("R: Received %d\n", buf);
		buf = 0;
		cond_continue((cond_var*)arg);
	}

	return NULL;
}

int main(void) {
	pthread_t prod, cons;
	cond_var cond;

	pthread_cond_init(&cond.cond, NULL);
	pthread_create(&prod, NULL, &tProducer, &cond);
	pthread_create(&cons, NULL, &tConsumer, &cond);

	sleep(MAIN_DELAY);

	pthread_cancel(prod);
	pthread_cancel(cons);


}
