#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);
double g(double);

void main() {
	double x;
	printf("Enter x: ");
	scanf("%lf", &x);
	
	printf("f(%lf) = %lf\n", x, f(x));
	printf("g(%lf) = %lf\n", x, g(x));
}

double f(double x) {
	return exp(-abs(x))*sin(x);
}

double g(double x) {
	return exp(-abs(x))*cos(x);
}

