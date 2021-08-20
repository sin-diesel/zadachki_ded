#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>

bool wasOverflow(double n)
{
	return isinf(n) || isnan(n);
}
double abs(double a)
{
	return a > 0 ? a : -a;
}
bool equal(double a, double b)
{
	return abs(a - b) < 0.00001;
}


void getCoefficients(double* a, double* b, double* c)
{
	printf("Enter coefficients of A*x^2 + B*x + C == 0\nA:");
	
	scanf("%lf", a);
	printf("B:");
	scanf("%lf", b);
	printf("C:");
	scanf("%lf", c);
}

void solveLinear(double a, double b)
{
	if (equal(a, 0.0))
	{
		if (equal(b, 0.0))
			printf("Roots are all real numbers");
		else
			printf("No roots");

	}
	else
		printf("x = %g", -b / a);

}

void solveQuadratic(double a, double b, double c)
{
	double b_half = b / 2;
	double D_divided_by_4 = pow(b_half, 2) - a * c;
	if (wasOverflow(D_divided_by_4))
	{
		printf("Overflow error");
	}
	else if (equal(D_divided_by_4, 0.0))
	{
		printf("x = %g", -b_half / a);
	}
	else if (D_divided_by_4 < 0)
	{
		printf("No roots");
	}
	else
	{
		double sq_root = sqrt(D_divided_by_4);
		printf("x1 = %g\n", (-b_half + sq_root) / a);
		printf("x2 = %g", (-b_half - sq_root) / a);
	}
}
int main()
{

	double a = 0, b = 0, c = 0;
	getCoefficients(&a, &b, &c);
	if (equal(a, 0.0))
		solveLinear(b, c);
	else
		solveQuadratic(a, b, c);
	
	getchar();

}