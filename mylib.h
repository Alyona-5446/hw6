typedef double func(double);

func f1, f2, f3, f4, f5, f6, f1_der, f2_der, f3_der, f4_der, f5_der, f6_der;
double root(func *, func *, func *, func *, double, double, double);
double integral(func *, double, double, double);
