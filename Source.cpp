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
bool isCorrectRootsAmount(int n)
{
	return n != EQUATION_RESULT_OVERFLOW_ERROR && n != EQUATION_RESULT_INFINITE_ROOTS;
}
int solveLinear(double a, double b, double * res)
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

int solveIncomplete(double a, double c, double* res)
{
	assert(res != nullptr);
	if (equal(c, 0.0))
	{
		res[0] = 0;
		return 1;
	}
	if (c > 0)
		return EQUATION_RESULT_NO_ROOTS;
	
	double mod = sqrt(-c) / a;
	res[0] = mod;
	res[1] = -mod;
	return 2;
}
int solveAlmostLinear(double a, double b, double* res)
{
	assert(!equal(b, 0) && res != nullptr);
	int lin_res = solveLinear(a, b, res);
	if (isCorrectRootsAmount(lin_res))
	{
		res[lin_res] = 0;
		return lin_res + 1;
	}
	return lin_res;
}
int solveEquation(double a, double b, double c, double* res)
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

enum TestResult
{
	TEST_RESULT_DONT_MATCH_ROOTS_AMOUNTS,
	TEST_RESULT_WRONG_ROOTS,
	TEST_RESULT_OK
};
void outErrorTestMessage(TestResult test, int amount, double * roots, int test_number)
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
void outTestMessage(TestResult test, int amount, double* roots, int test_number)
{
	assert(roots != nullptr);
	if (test == TEST_RESULT_OK)
		printf("Test %d: CORRECT\n", test_number);
	else
		outErrorTestMessage(test, amount, roots, test_number);
}
bool equalRootsArray(double* a, double* b, int size)
{
	for (int i = 0; i < size; ++i)
		if (!equal(a[i], b[i]) && !equal(a[size - i - 1], b[i]))
			return false;
	return true;
}
void  _testEquation(double a, double b, double c, int expected_amount_of_roots, double* expected_roots, int test_number)
{
	assert(expected_roots != nullptr);
	double roots[2];
	int amount = solveEquation(a, b, c, roots);
	if (amount != expected_amount_of_roots)
	{
		outTestMessage(TEST_RESULT_DONT_MATCH_ROOTS_AMOUNTS, amount, roots, test_number);
	}
	if (isCorrectRootsAmount(amount))
	{
		if (!equalRootsArray(roots, expected_roots, amount))
			outTestMessage(TEST_RESULT_WRONG_ROOTS, amount, roots, test_number);
		else
			outTestMessage(TEST_RESULT_OK, amount, roots, test_number);
	}
	else
		outTestMessage(TEST_RESULT_OK, amount, roots, test_number);


}
void  testEquation(double a, double b, double c, int expected_amount_of_roots, int test_number)
{
	double roots;
	_testEquation(a, b, c, expected_amount_of_roots, &roots, test_number);
}
void testEquation(double a, double b, double c, int expected_amount_of_roots, double root, int test_number)
{
	_testEquation(a, b, c, expected_amount_of_roots, &root, test_number);
}
void testEquation(double a, double b, double c, int expected_amount_of_roots, double r1, double r2, int test_number)
{
	double roots[2];
	roots[0] = r1;
	roots[1] = r2;
	_testEquation(a, b, c, expected_amount_of_roots, roots, test_number);
}
void testing()
{
	testEquation(1, -8, 15, 2, 3, 5, 1);
	testEquation(1, 2, 1, 1, -1, 2);
	testEquation(1, 3, 15, EQUATION_RESULT_NO_ROOTS, 3);
	testEquation(1, 0, -1, 2, 1, -1, 4);
	testEquation(0, 0, 3, EQUATION_RESULT_NO_ROOTS, 5);
	testEquation(0, 1, 3, 1, -3, 6);
	testEquation(0, 0, 0, EQUATION_RESULT_INFINITE_ROOTS, 7);

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