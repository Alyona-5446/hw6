#include <math.h>
#include "mylib.h"

int ITER_CNT; // iteration counter for root function

// auxiliary function to calculate f(x) - g(x) in root function
static double F(func *f, func *g, double x) {
	return f(x) - g(x);
}

// calculate root of f(x) = g(x) in [a; b] to within eps1 using Newton's method
double root(func *f, func *f_der, func *g, func *g_der,
			double a, double b, double eps1) {
	int der1 = (F(f, g, a) < 0);
	int der2 = (2 * F(f, g, (a + b) / 2) < F(f, g, a) + F(f, g, b));
	double cur = (der1 == der2 ? b : a);
	double delta = (der1 == der2 ? -eps1 : eps1);
	ITER_CNT = 0;
	do {
		cur -= F(f, g, cur) / F(f_der, g_der, cur);
		++ITER_CNT;
	} while ((F(f, g, cur) > 0) == (F(f, g, cur + delta) > 0));
	return cur;
}

// calculate integral of f(x) from a to b to within eps2 using Simpson's method
double integral(func *f, double a, double b, double eps2) {
	int n = 16;
	double h = (b - a) / n, ends = f(a) + f(b);
	double In, I2n, even = 0, odd = f(a + h);
	for (int i = 2; i < n; i += 2) {
		even += f(a + i * h);
		odd += f(a + (i + 1) * h);
	}
	I2n = (ends + 2 * even + 4 * odd) * h / 3;
	do {
		n *= 2, h /= 2;
		even += odd, odd = 0;
		for (int i = 1; i < n; i += 2) {
			odd += f(a + i * h);
		}
		In = I2n, I2n = (ends + 2 * even + 4 * odd) * h / 3;
	} while (fabs(In - I2n) >= 15 * eps2);
	return I2n;
}
