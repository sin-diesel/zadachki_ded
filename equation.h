#ifndef EQUATION_H
#define EQUATION_H
#include <limits.h>
#include <math.h>
enum EquationResult
{
	EQUATION_RESULT_OVERFLOW_ERROR = -1,
	EQUATION_RESULT_NO_ROOTS = 0,
	EQUATION_RESULT_INFINITE_ROOTS = INT_MAX
};

struct RootsPair
{
	double r1 = nan("");
	double r2 = nan("");
};

static const double PRECISION = 0.00001;

bool equal(double a, double b);
bool isCorrectRootsAmount(int n);
/// <summary>
/// solves quadratic equation at all cases
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="b">coefficient</param>
/// <param name="c">coefficient</param>
/// <param name="res">array where roots are written</param>
/// <returns>amount of roots</returns>
int solveEquation(double a, double b, double c, RootsPair * roots);
/// <summary>
/// writes result of quadratic equation to console with appropriate message
/// </summary>
void outResult(int amount_of_roots, const RootsPair * roots);
#endif
