#include <stdio.h>

#include "f.h"
#include "g.h"

void main() {
	double x;
	printf("Enter x: ");
	scanf("%lf", &x);
	
	printf("f(%lf) = %lf\n", x, f(x));
	printf("g(%lf) = %lf\n", x, g(x));
}

