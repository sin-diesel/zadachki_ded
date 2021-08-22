#include "equation.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "test.h"
/// <summary>
/// whites error test message to console with appropriate form
/// </summary>
/// <param name="test"></param>
/// <param name="amount"></param>
/// <param name="roots"></param>
/// <param name="test_number"></param>
void outErrorTestMessage(TestResult test, int amount, double roots[], int test_number)
{
	assert(roots != nullptr);
	printf("Error in test %d:\n", test_number);
	switch (test)
	{
	case TEST_RESULT_DONT_MATCH_ROOTS_AMOUNTS:
		printf("Amount of roots doesn't match, suggested amount = %d\n", amount);
		break;
	case TEST_RESULT_WRONG_ROOTS:
		printf("Roots doesnt match. Suggested roots:\n");
		outResult(amount, roots);
		break;

	default:
		printf("Uknown error\n");
	}
	getchar();
}
/// <summary>
/// writes any test result to console
/// </summary>
/// <param name="test"></param>
/// <param name="amount"></param>
/// <param name="roots"></param>
/// <param name="test_number"></param>
void outTestMessage(TestResult test, int amount, double roots[], int test_number)
{
	assert(roots != nullptr);
	if (test == TEST_RESULT_OK)
		printf("Test %d: CORRECT\n", test_number);
	else
		outErrorTestMessage(test, amount, roots, test_number);
}
/// <summary>
/// checks if sets of roots are match
/// </summary>
/// <param name="a">array with size up to 2</param>
/// <param name="b">array with size equall to size of a</param>
/// <param name="size">size of these two arrays</param>
/// <returns>true if sets are match independetly of order</returns>
bool equalRootsArray(double a[], double b[], int size)
{
	assert(a != nullptr && b != nullptr);
	for (int i = 0; i < size; ++i)
		if (!equal(a[i], b[i]) && !equal(a[size - i - 1], b[i]))
			return false;
	return true;
}


/// <summary>
/// gets equation and expected result, solves equation and checks if result is matching with expected
/// </summary>
/// <param name="a">coefficient</param>
/// <param name="b">coefficient</param>
/// <param name="c">coefficient</param>
/// <param name="expected_amount_of_roots"></param>
/// <param name="expected_roots"></param>
/// <param name="test_number"></param>
/// <param name="out">function that logs test result somehow</param>
/// <returns>true if test is correct and false otherwise</returns>
bool  systTestEquation(double a, double b, double c, int expected_amount_of_roots, double expected_roots[], int test_number, OutFunction out)
{
	assert(expected_roots != nullptr);
	double roots[2] = { nan(""), nan("") };
	int amount = solveEquation(a, b, c, roots);
	if (amount != expected_amount_of_roots)
	{
		if (out != nullptr)
			out(TEST_RESULT_DONT_MATCH_ROOTS_AMOUNTS, amount, roots, test_number);
		return false;
	}
	if (isCorrectRootsAmount(amount))
	{
		if (!equalRootsArray(roots, expected_roots, amount))
		{
			if (out != nullptr)
				out(TEST_RESULT_WRONG_ROOTS, amount, roots, test_number);
			return false;
		}
		else
		{
			if (out != nullptr)
				out(TEST_RESULT_OK, amount, roots, test_number);
			return true;
		}
	}
	if (out != nullptr)
		out(TEST_RESULT_OK, amount, roots, test_number);
	return true;


}

bool  testEquation(double a, double b, double c, int expected_amount_of_roots, int test_number, OutFunction out)
{
	double roots = nan("");
	return systTestEquation(a, b, c, expected_amount_of_roots, &roots, test_number, out);
}
bool testEquation(double a, double b, double c, int expected_amount_of_roots, double root, int test_number, OutFunction out)
{
	return systTestEquation(a, b, c, expected_amount_of_roots, &root, test_number, out);
}
bool testEquation(double a, double b, double c, int expected_amount_of_roots, double r1, double r2, int test_number, OutFunction out)
{
	double roots[2] = { r1, r2 };
	return systTestEquation(a, b, c, expected_amount_of_roots, roots, test_number, out);
}
/// <summary>
/// test solving equation module on some prepared tests
/// </summary>

void testing()
{
	testEquation(1, -8, 15, 2, 3, 5, 1, outTestMessage);
	testEquation(1, 2, 1, 1, -1, 2, outTestMessage);
	testEquation(1, 3, 15, EQUATION_RESULT_NO_ROOTS, 3, outTestMessage);
	testEquation(1, 0, -1, 2, 1, -1, 4, outTestMessage);
	testEquation(0, 0, 3, EQUATION_RESULT_NO_ROOTS, 5, outTestMessage);
	testEquation(0, 1, 3, 1, -3, 6, outTestMessage);
	testEquation(0, 0, 0, EQUATION_RESULT_INFINITE_ROOTS, 7, outTestMessage);

}