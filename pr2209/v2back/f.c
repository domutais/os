#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
	double x;
	if (argc < 2) {
		printf("Enter x: ");
		scanf("%lf", &x);
	}
	else x = strtod(argv[1], NULL);
	
	printf("f(%lf) = %lf\n", x, exp(-abs(x))*sin(x));
	
	return 0;
}	
