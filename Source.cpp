#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

enum EquationResult
{
	EQUATION_RESULT_OVERFLOW_ERROR = -1,
	EQUATION_RESULT_NO_ROOTS = 0,
	EQUATION_RESULT_INFINITE_ROOTS = INT_MAX
};

bool wasOverflow(double n)
{
	return isinf(n) || isnan(n);
}
double abs(double a)
{
	return a > 0 ? a : -a;
}

const double PRECISION = 0.00001;
bool equal(double a, double b)
{
	return abs(a - b) < PRECISION;
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

int solveLinear(double a, double b, double * res)
{
	if (equal(a, 0.0))
	{
		if (equal(b, 0.0))
			return EQUATION_RESULT_INFINITE_ROOTS;
		else
			return EQUATION_RESULT_NO_ROOTS;

	}
	else
	{
		
		res[0] = -b / a;
		return 1;
	}

}

int solveQuadratic(double a, double b, double c, double * res)
{
	assert(res != nullptr);
	double b_half = b / 2;
	double D_divided_by_4 = b_half * b_half - a * c;
	if (wasOverflow(D_divided_by_4))
	{
		return EQUATION_RESULT_OVERFLOW_ERROR;
	}
	else if (equal(D_divided_by_4, 0.0))
	{
		
		res[0] = -b_half / a;
		return 1;
	}
	else if (D_divided_by_4 < 0)
	{
		return EQUATION_RESULT_NO_ROOTS;
	}
	else
	{
		double sq_root = sqrt(D_divided_by_4);
		res[0] = (-b_half + sq_root) / a;
		res[1] = (-b_half - sq_root) / a;
		return 2;
	}
}

int solveEquation(double a, double b, double c, double* res)
{
	assert(res != nullptr);
	if (equal(a, 0.0))
		return solveLinear(b, c, res);
	return solveQuadratic(a, b, c, res);
}

void outResult(int amount_of_roots, double* roots)
{
	assert(roots != nullptr);
	switch (amount_of_roots)
	{
	case EQUATION_RESULT_OVERFLOW_ERROR:
		printf("Overflow error\n");
		break;
	case EQUATION_RESULT_NO_ROOTS:
		printf("No roots\n");
		break;
	case 1:
		printf("x = %g\n", *roots);
		break;
	case 2:
		printf("x1 = %g\nx2 = %g\n", roots[0], roots[1]);
		break;
	case EQUATION_RESULT_INFINITE_ROOTS:
		printf("All reals are roots\n");
		break;
	default:
		assert(false);
	}
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
	
	double roots[2] = { nan(""), nan("") };
	int amount_of_roots = solveEquation(a, b, c, roots);
	outResult(amount_of_roots, roots);
	getchar();

}