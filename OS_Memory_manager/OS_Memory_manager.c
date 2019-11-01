#include "unit_test.h"
#include "load_test.h"

int main ()
{
	init_unit_testing_env();
	run_all_unit_tests();

	init_load_testing_env();
	run_all_load_tests();

	return 0;
}
