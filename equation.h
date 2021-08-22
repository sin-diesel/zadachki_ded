#ifndef EQUATION_H
#define EQUATION_H
#include <limits.h>
enum EquationResult
{
	EQUATION_RESULT_OVERFLOW_ERROR = -1,
	EQUATION_RESULT_NO_ROOTS = 0,
	EQUATION_RESULT_INFINITE_ROOTS = INT_MAX
};

static const double PRECISION = 0.00001;

bool equal(double a, double b);
bool isCorrectRootsAmount(int n);
int solveEquation(double a, double b, double c, double res[]);
void outResult(int amount_of_roots, double roots[]);
#endif
