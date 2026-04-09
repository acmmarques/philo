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

void test_init(void)
{
	printf("\n[ Suite: Initialization ]\n");

	t_table table;
	char *args[] = {"./philo", "5", "800", "200", "200", "7", NULL};

	// 1. Test return value of init
	assert_test(init_table(&table, 6, args) == 0, "Init: Returns 0 on success");

	// 2. Test basic value assignment
	assert_test(table.philo_count == 5, "Init: philo_count is 5");
	assert_test(table.time_to_die == 800, "Init: time_to_die is 800");
	assert_test(table.required_meals == 7, "Init: must_eat_count is 7");

	// 3. Test memory allocation
	assert_test(table.philos != NULL, "Init: Philos array is allocated");
	assert_test(table.forks != NULL, "Init: Forks array is allocated");

	if (table.philos && table.forks)
	{
		// 4. Test Philosopher Setup
		assert_test(table.philos[0].id == 1, "Init: Philo 0 has ID 1");
		assert_test(table.philos[4].id == 5, "Init: Philo 4 has ID 5");

		// 5. Test Table Topology (The Circular Forks)
		assert_test(table.philos[0].left_fork == &table.forks[0], "Init: Philo 1 left fork is fork 0");
		assert_test(table.philos[0].right_fork == &table.forks[1], "Init: Philo 1 right fork is fork 1");

		// The most critical test: Does the last philosopher wrap around?
		assert_test(table.philos[4].left_fork == &table.forks[4], "Init: Philo 5 left fork is fork 4");
		assert_test(table.philos[4].right_fork == &table.forks[0], "Init: Philo 5 right fork wraps to fork 0");

		// Clean up memory and destroy mutexes so the test runner doesn't leak!
		free_table(&table);
	}
}
// ---------------------------------------------------------

int main(void)
{
	printf("\n--- STARTING TDD SUITE ---\n");

	test_parser();
	test_init();

	printf("--- RESULTS: %d/%d PASSED ---\n\n", g_tests_passed, g_tests_run);

	if (g_tests_passed == g_tests_run)
		return (0);
	return (1);
}
