#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define B 2
#define A 0


double f(double x) { return 4 - x*x; }

typedef struct arg {
	double a;
	double b;
} arg_t;

double result = 0.0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* tcalc(void *arg) {
	arg_t bounds = *(arg_t*)arg;
	
	double add = f(bounds.a + (bounds.b - bounds.a)/2);
	printf("[%lf, %lf] = %lf\n", bounds.a, bounds.b, add);
	pthread_mutex_lock(&mutex);
	result += add;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(int argc, char** argv) {
	int threads = 15;
	if (argc > 1) threads = atoi(argv[1]);

	pthread_t *thr_arr = malloc(threads*sizeof(pthread_t));
	arg_t *bounds = malloc(threads*sizeof(arg_t));
	double h = (double)(B - A) / threads;
	double xi = A;
	for (int i = 0; i < threads; i++) {
		bounds[i] = (arg_t){xi, xi + h};
		xi += h;
		pthread_create(&thr_arr[i], NULL, &tcalc, &bounds[i]);
	}

	for (int i = 0; i < threads; i++) {
		pthread_join(thr_arr[i], NULL);
	}

	result *= h;
	printf("result = %lf\n", result);
}
