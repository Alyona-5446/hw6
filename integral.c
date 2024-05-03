#include <float.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include "mylib.h"

enum mode {GET_AREA, TEST_ROOT, TEST_INTEGRAL}; // enum with possible launch modes

extern int ITER_CNT; // iteration counter for root function
static int PRINT_ROOTS, PRINT_ITERS; // flags corresponding to --root and --iterations
// arrays with possible functions for root and integral tests and their derivatives
static func *fs[] = {f1, f2, f3, f4, f5, f6}, *ders[] = {f1_der, f2_der, f3_der, f4_der, f5_der, f6_der};

static void print_help(void) {
	printf("%s", "This program supports the following options:\n\
	-h or --help to print all supported options\n\
	-r or --root to print roots of f1 = f2, f1 = f3 and f2 = f3\n\
	-i or --iterations to print number of iterations performed by root function\n\
	-R <F1:F2:A:B:E:R> or --test-root <F1:F2:A:B:E:R> to test root function\n\
	-I <F:A:B:E:R> or --test-integral <F:A:B:E:R> to test integral function\n\n");
}

// auxiliary function for root tests
static double get_root(int idx1, int idx2, double a, double b, double eps1) {
	double r = root(fs[idx1], ders[idx1], fs[idx2], ders[idx2], a, b, eps1);
	if (PRINT_ROOTS) {
		printf("Root of f%d = f%d in [%g; %g]: %g\n", idx1 + 1, idx2 + 1, a, b, r);
	}
	if (PRINT_ITERS) {
		printf("Number of iterations for f%d = f%d in [%g; %g]: %d\n", idx1 + 1, idx2 + 1, a, b, ITER_CNT);
	}
	return r;
}

static void test_root(char *arg) {
	int idx1, idx2;
	double a, b, eps1, ans;
	if (sscanf(arg, "%d:%d:%lf:%lf:%lf:%lf", &idx1, &idx2, &a, &b, &eps1, &ans) != 6) {
		fprintf(stderr, "%s", "Invalid optarg format :(\nUse -h or --help for format info\n\n");
		return;
	}
	PRINT_ROOTS = 1;
	double res = get_root(idx1 - 1, idx2 - 1, a, b, eps1);
	if (fabs(ans) < DBL_MIN) {
		printf("Absolute error: %g\nRelative error: n/a\n\n", fabs(res));
	} else {
		printf("Absolute error: %g\nRelative error: %g\n\n", fabs(res - ans), fabs((res - ans) / ans));
	}
}

static void test_integral(char *arg) {
	int idx;
	double a, b, eps2, ans;
	if (sscanf(arg, "%d:%lf:%lf:%lf:%lf", &idx, &a, &b, &eps2, &ans) != 5) {
		fprintf(stderr, "%s", "Invalid optarg format :(\nUse -h or --help for format info\n\n");
		return;
	}
	double res = integral(fs[idx - 1], a, b, eps2);
	printf("Integral of f%d from %g to %g: %g\n", idx, a, b, res);
	if (fabs(ans) < DBL_MIN) {
		printf("Absolute error: %g\nRelative error: n/a\n\n", fabs(res));
	} else {
		printf("Absolute error: %g\nRelative error: %g\n\n", fabs(res - ans), fabs((res - ans) / ans));
	}
}

// calculate area between f1, f2 and f3
static void get_area(void) {
	double r12 = get_root(0, 1, 1, 2, 1e-5);
	double r13 = get_root(0, 2, -2, -1, 1e-5);
	double r23 = get_root(1, 2, 0, 1, 1e-5);
	double area = integral(f1, r13, r12, 1e-5) - integral(f3, r13, r23, 1e-5) - integral(f2, r23, r12, 1e-5);
	printf("Area between f1, f2 and f3: %g\n\n", area);
}

int main(int argc, char *argv[]) {
	static struct option longopts[] = {
		{"help", no_argument, NULL, 'h'},
		{"root", no_argument, NULL, 'r'},
		{"iterations", no_argument, NULL, 'i'},
		{"test-root", required_argument, NULL, 'R'},
		{"test-integral", required_argument, NULL, 'I'},
		{NULL, 0, NULL, 0}
	};
	char *arg = NULL;
	int opt, launch = GET_AREA;
	printf("%c", '\n');
	while ((opt = getopt_long(argc, argv, "hriR:I:", longopts, NULL)) != -1) {
		switch (opt) {
			case 'h':
				print_help();
				break;
			case 'r':
				PRINT_ROOTS = 1;
				break;
			case 'i':
				PRINT_ITERS = 1;
				break;
			case 'R':
				launch = TEST_ROOT, arg = optarg;
				break;
			case 'I':
				launch = TEST_INTEGRAL, arg = optarg;
				break;
			case '?':
				fprintf(stderr, "%s", "Use -h or --help for option info\n\n");
				break;
			default:
				break;
		}
	}
	switch (launch) {
		case GET_AREA:
			get_area();
			break;
		case TEST_ROOT:
			test_root(arg);
			break;
		case TEST_INTEGRAL:
			test_integral(arg);
			break;
		default:
			break;
	}
	return 0;
}
