#include "philo.h"

int g_tests_run = 0;
int g_tests_passed = 0;

/* 
 * A simple evaluation function.
 * If 'condition' is 0, the test fails. If it is 1, it passes.
 */
void assert_test(int condition, const char *test_name)
{
	g_tests_run++;
	if (condition)
	{
		g_tests_passed++;
		printf("\033[0;32m[OK]\033[0m %s\n", test_name);
	}
	else
	{
		printf("\033[0;31m[KO]\033[0m %s\n", test_name);
	}
}

// ---------------------------------------------------------
// YOUR TESTS GO HERE
// ---------------------------------------------------------

void test_parser(void)
{
	printf("\n[ Suite: Argument Parsing ]\n");

	// 1. Valid arguments (4 args + program name = argc 5)
	char *valid_4[] = {"./philo", "5", "800", "200", "200", NULL};
	assert_test(check_args(5, valid_4) == 0, "Valid: 4 parameters");

	// 2. Valid arguments (5 args + program name = argc 6)
	char *valid_5[] = {"./philo", "5", "800", "200", "200", "7", NULL};
	assert_test(check_args(6, valid_5) == 0, "Valid: 5 parameters");

	// 3. Invalid argument count
	char *invalid_argc[] = {"./philo", "5", "800", NULL};
	assert_test(check_args(3, invalid_argc) == 1, "Invalid: Not enough arguments");

	// 4. Invalid characters
	char *invalid_chars[] = {"./philo", "5", "800a", "200", "200", NULL};
	assert_test(check_args(5, invalid_chars) == 1, "Invalid: Contains letters");

	// 5. Negative numbers
	char *invalid_neg[] = {"./philo", "5", "-800", "200", "200", NULL};
	assert_test(check_args(5, invalid_neg) == 1, "Invalid: Negative number");

	// 6. Positive numbers
	char *valid_pos[] = {"./philo", "5", "+800", "200", "+200", NULL};
	assert_test(check_args(5, valid_pos) == 0, "Valid: Positive numbers with + sign");
}

void test_other_thing(void)
{
	printf("\n[ Suite: Argument Parsing ]\n");
}

// ---------------------------------------------------------

int main(void)
{
	printf("\n--- STARTING TDD SUITE ---\n");

	test_parser();

	printf("--- RESULTS: %d/%d PASSED ---\n\n", g_tests_passed, g_tests_run);

	if (g_tests_passed == g_tests_run)
		return (0);
	return (1);
}
