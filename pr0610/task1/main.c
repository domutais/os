#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc != 4) {
		printf("Arguments: [a] [b] [c]\n    where a, b, c are the coefficients of the quadratic\n    a*x^2 + b*x + c\n");
		return 0;
	}

	double a, b, c;

	a = atof(argv[1]);
	b = atof(argv[2]);
	c = atof(argv[3]);
	
	double D = b*b - 4*a*c;

	if (a == 0.0) {
		printf("This equation is not a quadratic (a is equal to 0).\n");
		return 0;
	}

	if (D < 0) {
		printf("This equation has no real roots.\n");
		return 0;
	}

	double x1 = (-b - sqrt(D)) / 2*a;
	double x2 = (-b + sqrt(D)) / 2*a;

	printf("This equation has roots: %f, %f.\n", x1, x2);
	printf("%f*x^2 %c %f*x %c %f = (x %c %f)(x %c %f)\n", a, (b >= 0 ? '+' : '-'), fabs(b), (c >= 0 ? '+' : '-'), fabs(c), 
			(x1 >= 0 ? '-' : '+'), fabs(x1), (x2 >= 0 ? '-' : '+'), fabs(x2));


	return 0;
}
