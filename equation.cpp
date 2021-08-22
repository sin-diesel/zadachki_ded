#include <math.h>
#include <assert.h>
#include "equation.h"
#include <stdio.h>


bool wasOverflow(double n)
{
	return isinf(n) || isnan(n);
}



bool equal(double a, double b)
{
	return fabs(a - b) < PRECISION;
}
bool isCorrectRootsAmount(int n)
{
	return n != EQUATION_RESULT_OVERFLOW_ERROR && n != EQUATION_RESULT_INFINITE_ROOTS;
}
/// <summary>
/// Solves linear equation
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="b">coefficient</param>
/// <param name="res">array where root is written</param>
/// <returns>amount of roots</returns>
int solveLinear(double a, double b, RootsPair* res)
{
	assert(res != nullptr);
	if (equal(a, 0.0))
	{
		if (equal(b, 0.0))
			return EQUATION_RESULT_INFINITE_ROOTS;
		else
			return EQUATION_RESULT_NO_ROOTS;

	}
	else
	{

		res->r1 = -b / a;
		return 1;
	}

}
/// <summary>
/// solves full quadratic equation
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="b">coefficient</param>
/// <param name="c">coefficient</param>
/// <param name="res">array where roots are written</param>
/// <returns>amount of roots</returns>
int solveQuadratic(double a, double b, double c, RootsPair* res)
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

		res->r1 = -b_half / a;
		return 1;
	}
	else if (D_divided_by_4 < 0)
	{
		return EQUATION_RESULT_NO_ROOTS;
	}
	else
	{
		double sq_root = sqrt(D_divided_by_4);
		res->r1 = (-b_half + sq_root) / a;
		res->r2 = (-b_half - sq_root) / a;
		return 2;
	}
}
/// <summary>
/// solves quadratic equation without coefficient of linear member
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="c">coefficient</param>
/// <param name="res">array where roots are written</param>
/// <returns>amount of roots</returns>
int solveIncomplete(double a, double c, RootsPair* res)
{
	assert(res != nullptr);
	if (equal(c, 0.0))
	{
		res->r1 = 0;
		return 1;
	}
	if (c > 0)
		return EQUATION_RESULT_NO_ROOTS;

	double mod = sqrt(-c) / a;
	res->r1 = mod;
	res->r2 = -mod;
	return 2;
}
/// <summary>
/// solves quadratic equation that looks like x(ax+b)==0
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="b">coefficient</param>
/// <param name="res">array where roots are written</param>
/// <returns>amount of roots</returns>
int solveAlmostLinear(double a, double b, RootsPair* res)
{
	assert(!equal(b, 0) && res != nullptr);
	int lin_res = solveLinear(a, b, res);
	if (isCorrectRootsAmount(lin_res))
	{
		if (lin_res == 0)
			res->r1 = 0;
		else
			res->r2 = 0;
		return lin_res + 1;
	}
	return lin_res;
}

int solveEquation(double a, double b, double c, RootsPair* res)
{
	assert(res != nullptr);
	if (equal(a, 0.0))
		return solveLinear(b, c, res);
	else if (equal(b, 0.0))
		return solveIncomplete(a, c, res);
	else if (equal(c, 0.0))
		return solveAlmostLinear(a, b, res);
	return solveQuadratic(a, b, c, res);
}


void outResult(int amount_of_roots, const RootsPair* roots)
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
		printf("x = %g\n", roots->r1);
		break;
	case 2:
		printf("x1 = %g\nx2 = %g\n", roots->r1, roots->r2);
		break;
	case EQUATION_RESULT_INFINITE_ROOTS:
		printf("All reals are roots\n");
		break;
	default:
		assert(false);
	}
}
