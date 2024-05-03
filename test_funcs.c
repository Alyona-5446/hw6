#include <math.h>
#include "mylib.h"

double f4(double x) { // f4(x) = -x^2 - 4x - 3
	return -(x + 3) * (x + 1);
}

double f4_der(double x) { // f4'(x) = -2x - 4
	return -2 * x - 4;
}

double f5(double x) { // f5(x) = x^3 - 7x + 6
	return (x + 3) * (x - 1) * (x - 2);
}

double f5_der(double x) { // f5'(x) = 3x^2 - 7
	return 3 * x * x - 7;
}

double f6(double x) { // f6(x) = 4^{x} - 4
	return pow(4, x) - 4;
}

double f6_der(double x) { // f6'(x) = 4^{x}ln4
	return 2 * pow(4, x) * M_LN2;
}
