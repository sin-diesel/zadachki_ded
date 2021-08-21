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
double absol(double a)
{
	return a > 0 ? a : -a;
}

const double PRECISION = 0.00001;
bool equal(double a, double b)
{
	return absol(a - b) < PRECISION;
}
void clearBuff()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
/// <summary>
/// Запрашивает у пользователя значение double через консоль до тех пор, пока он не введет корректное
/// </summary>
/// <returns>Запрошенное значение</returns>
double getValue()
{
	double value = nan("");

	scanf("%lf", &value);
	while (isnan(value))
	{
		clearBuff();
		printf("\nIncorrect input, enter again: ");
		scanf("%lf", &value);
	}
	return value;
}
/// <summary>
/// Запрашивает у пользователя из консоли коэффициенты квадратного уравнения
/// </summary>
void getCoefficients(double* a, double* b, double* c)
{
	assert(a != nullptr && b != nullptr && c != nullptr);
	printf("Enter coefficients of A*x^2 + B*x + C == 0\nA:");
	
	*a = getValue();
	printf("B:");
	*b = getValue();
	printf("C:");
	*c = getValue();
}
bool isCorrectRootsAmount(int n)
{
	return n != EQUATION_RESULT_OVERFLOW_ERROR && n != EQUATION_RESULT_INFINITE_ROOTS;
}
/// <summary>
/// Решает линейное уравнение
/// </summary>
/// <param name="res">Массив куда запишется корень</param>
/// <returns>Количество корней</returns>
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
/// <summary>
/// Решает квадратное полное невырожденное уравнение
/// </summary>
/// <param name="res">Массив куда запишутся корни</param>
/// <returns>Количество корней уравнения</returns>
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
/// <summary>
/// Решает квадратное уравнение с отсутствующим линейным членом
/// </summary>
/// <param name="res">Массив куда запишутся корни</param>
/// <returns>Количество корней</returns>
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
/// <summary>
/// Решает квадратное уравнение вида x(ax+b) == 0
/// </summary>
/// <param name="res">массив куда запишутся корни</param>
/// <returns>Количество корней</returns>
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
/// <summary>
/// Решает квадратное уравнение во всех вариантах
/// </summary>
/// <param name="res">Массив куда запишутся корни</param>
/// <returns>Количество корней</returns>
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
/// <summary>
/// Выводит результат решения квадратного уравнения в консоль
/// </summary>
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
/// <summary>
/// Выводит сообщение об ошибке в тесте в консоль
/// </summary>
/// <param name="test">Тип  ошибки</param>
/// <param name="amount">Количество получившихся корней уравнения</param>
/// <param name="roots">Получившиеся корни</param>
/// <param name="test_number">Номер теста</param>
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
/// <summary>
/// Выводит сообщение о результате теста
/// </summary>
/// <param name="test">Тип результата: корректно или тип ошибки</param>
/// <param name="amount">Количество получившихся корней уравнения</param>
/// <param name="roots">Получившиеся корни</param>
/// <param name="test_number">Номер теста</param>
void outTestMessage(TestResult test, int amount, double* roots, int test_number)
{
	assert(roots != nullptr);
	if (test == TEST_RESULT_OK)
		printf("Test %d: CORRECT\n", test_number);
	else
		outErrorTestMessage(test, amount, roots, test_number);
}
/// <summary>
/// Проверяет равны ли множества корней квадратного уравнения
/// </summary>
/// <returns>true если множества равны независимо от порядка и false иначе</returns>
bool equalRootsArray(double* a, double* b, int size)
{
	for (int i = 0; i < size; ++i)
		if (!equal(a[i], b[i]) && !equal(a[size - i - 1], b[i]))
			return false;
	return true;
}

typedef void (*OutFunction)(TestResult, int, double*, int);
/// <summary>
/// Производит тестирование уравнения: принимает коэффициенты уравнения и ожидаемый результат, вычисляет собственный ответ и сравнивает
/// </summary>
/// <param name="out">Функция, которая выведет результат теста (куда - неважно). Если nullptr, то вывод игнорируется</param>
/// <returns>true если тест верный и false иначе</returns>
bool  systTestEquation(double a, double b, double c, int expected_amount_of_roots, double* expected_roots, int test_number, OutFunction out)
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
/// Производит тестирование решения квадратного уравнения на некотором наборе примеров
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