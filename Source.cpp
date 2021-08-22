#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include "equation.h"
#include "test.h"

/// <summary>
/// asks for enter double input to console until input is correct
/// </summary>
/// <returns>entered input</returns>
double getValue(const char * message)
{
	double value = nan("");
	if (message != nullptr)
		printf(message);

	scanf("%lf", &value);
	while (isnan(value) || getchar() != '\n')
	{
		rewind(stdin);
		printf("\nIncorrect input, enter again: ");
		scanf("%lf", &value);
	}
	return value;
}
/// <summary>
/// gets coefficients for quadratic equation from user by console input
/// </summary>
/// <param name="a">first coefficient</param>
/// <param name="b">second coefficient</param>
/// <param name="c">third coefficient</param>
void getCoefficients(double* a, double* b, double* c)
{
	assert(a != nullptr && b != nullptr && c != nullptr);
	printf("Enter coefficients of A*x^2 + B*x + C == 0\n");
	
	*a = getValue("A:");
	*b = getValue("B:");
	*c = getValue("C:");
}




int main()
{
	testing();

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