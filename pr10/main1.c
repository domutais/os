#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUF_SIZE 2
#define DELAY 10

typedef struct buffer {
	int *buf;
	int len;
	sem_t sem;
	sem_t lock;
} buf_t;

void buf_init(buf_t *b, int size) {
	b->buf = (int*)calloc(size, sizeof(int));
	b->len = size;
	sem_init(&b->sem, 0, 0);
	sem_init(&b->lock, 0, 1);
}

int buf_push(buf_t *b, int val) {
	sem_wait(&b->lock);

	int ptr;
	sem_getvalue(&b->sem, &ptr);
	if (ptr >= b->len) {
	       	sem_post(&b->lock);
		return -1;
	}

	(b->buf)[ptr] = val;
	sem_post(&b->sem);
	sem_post(&b->lock);
	return 0;
}

int buf_pop(buf_t *b) {
	int ptr;
	sem_wait(&b->sem);
	sem_wait(&b->lock);
	sem_getvalue(&b->sem, &ptr); 
	
	int ret = (b->buf)[ptr];
	(b->buf)[ptr] = 0;
	
	sem_post(&b->lock);
	return ret;
}

void *tProducer(void *arg) {
	buf_t *b = (buf_t*)arg;

	while(1) {
		int n = rand() % 15 + 1;
		printf("Producer: Ready to push (%d)\n", n);
		printf("Producer: Tried to push %d - %s\n", n, !buf_push(b, n) ? "success" : "failure");
		sleep(0.01);
	}

	return NULL;
}

void *tConsumer(void *arg) {
	buf_t *b = (buf_t*)arg;

	while(1) {
		printf("Consumer: Ready to receive\n");
		int n = buf_pop(b);
		printf("Consumer: Tried to recieve - recieved %d (%s)\n", n, n ? "success" : "failure");
		sleep(0.01);
	}

	return NULL;
}

int main(void) {
	srand(time(NULL));
	buf_t b;
	buf_init(&b, BUF_SIZE);

	pthread_t producer, consumer;
	pthread_create(&producer, NULL, &tProducer, &b);
	pthread_create(&consumer, NULL, &tConsumer, &b);

	printf("Master: threads started.\n");
	
	sleep(DELAY);

	pthread_cancel(producer);
	pthread_cancel(consumer);

	printf("Master: threads canceled.\n");

	return 0;

}
