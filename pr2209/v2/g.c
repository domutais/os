#include <math.h>
#include <stdlib.h>

#include "g.h"

double g(double x) {
	return exp(-abs(x))*cos(x);
}
