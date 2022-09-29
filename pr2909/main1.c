#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6

int main(void) {
	srand(time(NULL));

	double array[N];
	
	double average = 0.0;
	int firstNegative = -1;

	int i;
	for(i = 0; i < N; i++) {
		array[i] = (double)(rand()%100000 - 50000)/(rand()%1000);
		
		printf("%f ", array[i]);

		average = (average * i + array[i]) / (i+1);

		if (array[i] < 0.0 && firstNegative < 0) firstNegative = i;

	}
	printf("\nTotal: %d elements.\n", N);


	int greaterThanAvg = 0;
	double sumAbs = 0.0;
	for(i = 0; i < N; i++) {
		if (array[i] > average) greaterThanAvg++;

		if (i > firstNegative) sumAbs += (array[i] >= 0 ? array[i] : -array[i]);
	}

	printf("Average: %f\nGreater than average: %d\n", average, greaterThanAvg);
	printf("Sum of abs. values of elements after the first negative: %f\n", sumAbs);

	exit(0);
}


