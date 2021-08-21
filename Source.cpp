#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
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
	assert(a != nullptr && b != nullptr && c != nullptr);
	printf("Enter coefficients of A*x^2 + B*x + C == 0\nA:");
	
	scanf("%lf", a);
	printf("B:");
	scanf("%lf", b);
	printf("C:");
	scanf("%lf", c);
}

int solveLinear(double a, double b, double ** res)
{
	if (equal(a, 0.0))
	{
		if (equal(b, 0.0))
			return INT_MAX;
		else
			return 0;

	}
	else
	{
		*res = new double[1];
		**res = -b / a;
		return 1;
	}

}

int solveQuadratic(double a, double b, double c, double ** res)
{
	double b_half = b / 2;
	double D_divided_by_4 = b_half * b_half - a * c;
	if (wasOverflow(D_divided_by_4))
	{
		return -1;
	}
	else if (equal(D_divided_by_4, 0.0))
	{
		*res = new double[1];
		**res = -b_half / a;
		return 1;
	}
	else if (D_divided_by_4 < 0)
	{
		return 0;
	}
	else
	{
		double sq_root = sqrt(D_divided_by_4);
		*res = new double[2];
		(*res)[0] = (-b_half + sq_root) / a;
		(*res)[1] = (-b_half - sq_root) / a;
		return 2;
	}
}

int solveEquation(double a, double b, double c, double** res)
{
	assert(res != nullptr && *res == nullptr);
	if (equal(a, 0.0))
		return solveLinear(b, c, res);
	return solveQuadratic(a, b, c, res);
}

void outResult(int amount_of_roots, double* roots)
{
	if (amount_of_roots == -1)
		printf("Overflow error\n");
	else if (amount_of_roots == 0)
		printf("No roots\n");
	else if (amount_of_roots == 1)
		printf("x = %g\n", *roots);
	else if (amount_of_roots == 2)
		printf("x1 = %g\nx2 = %g\n", roots[0], roots[1]);
	else if (amount_of_roots == INT_MAX)
		printf("All reals are roots\n");
	else
		assert(false);
}
int main()
{

	double a = nan(""), b = nan(""), c = nan("");
	getCoefficients(&a, &b, &c);
	if (isnan(a) || isnan(b) || isnan(c))
	{
		printf("Error in input");
		return 0;
	}
	
	double * roots = nullptr;
	int amount_of_roots = solveEquation(a, b, c, &roots);
	outResult(amount_of_roots, roots);
	delete[] roots;
	getchar();

}