#include <math.h>
#include <stdlib.h>

#include "f.h"

double f(double x) {
	return exp(-abs(x))*sin(x);
}
