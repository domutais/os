#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N_CATALAN 11
#define N_PRIMES 20

long long newCatalan(int);

void* tCatalan(void* arg) {
	for (int i = 0; i < N_CATALAN; i++) {
		((long long*)arg)[i] = newCatalan(i+1);
	}

	return NULL;
}

long long newCatalan (int n) {
	long long res = 1;

	for (int i = 2*n; i > 1; i--) {
		if (i > n+1) res *= i;
		if (i < n+1) res /= i;
	}

	return res;
}

void* tPrimes(void* arg) {
	if (N_PRIMES < 1) return NULL;

	for (int i = 0; i < N_PRIMES; i++) {
		int prime;
		int last_j = 1;

		if (i == 0) prime = 2;
		else if (i == 1) prime = 3;
		else if (i == 2) prime = 5;
		else {
			for (int j = last_j; 1; j++) {
				int remainders[] = {1, 5};
				int is_prime = 1;
				prime = 6*(j/2) + remainders[(j)%2];
				for (int k = 0; k < i; k++) if (prime % ((int*)arg)[k] == 0) is_prime = 0;
		
				if (is_prime) {
					last_j = j;
					break;
				}
			}	
		}
		((int*)arg)[i] = prime;
	}

	return NULL;
}

		
	

int main(void) {
	pthread_t catalan, primes;

	long long arr_catalan[N_CATALAN];
	int arr_primes[N_PRIMES];

	if (pthread_create(&catalan, NULL, &tCatalan, arr_catalan) != 0) fprintf(stderr, "Failed to start catalan\n");
	if (pthread_create(&primes, NULL, &tPrimes, arr_primes) != 0) fprintf(stderr, "Failed to start primes\n");

	if(pthread_join(catalan, NULL) != 0 ) fprintf(stderr, "Failed to join catalan\n");
	else {
		printf("Finished counting first %d Catalan numbers. Here they are:\n", N_CATALAN);
		for (int i = 0; i < N_CATALAN; i++) printf("\t%lld\n", arr_catalan[i]);
	}

	if(pthread_join(primes, NULL) != 0) fprintf(stderr, "Failed to join primes\n");
	else {
		printf("Finished generating first %d primes. Here they are:\n", N_PRIMES);
		for (int i = 0; i < N_PRIMES; i++) printf("\t%d\n", arr_primes[i]);
	}
	
	printf("This program used function arguments (via pthread_create) to transmit data.\n");

	return 0;
}
