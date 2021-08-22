#ifndef TEST_H
#define TEST_H
/// <summary>
/// test solving equation module on some prepared tests
/// </summary>
void testing();

enum TestResult
{
	TEST_RESULT_DONT_MATCH_ROOTS_AMOUNTS,
	TEST_RESULT_WRONG_ROOTS,
	TEST_RESULT_OK
};
typedef void (*OutFunction)(TestResult, int, const RootsPair* res, int);
/// <summary>
/// Test one equation
/// </summary>
/// <param name="out">Function that logs test result somewhere</param>
/// <returns>true if test is correct and false otherwise</returns>
bool testEquation(double a, double b, double c, int expected_amount_of_roots, int test_number, OutFunction out);
/// <summary>
/// Test one equation
/// </summary>
/// <param name="out">Function that logs test result somewhere</param>
/// <returns>true if test is correct and false otherwise</returns>
bool testEquation(double a, double b, double c, int expected_amount_of_roots, double root, int test_number, OutFunction out);
/// <summary>
/// Test one equation
/// </summary>
/// <param name="out">Function that logs test result somewhere</param>
/// <returns>true if test is correct and false otherwise</returns>
bool testEquation(double a, double b, double c, int expected_amount_of_roots, double r1, double r2, int test_number, OutFunction out);
#endif