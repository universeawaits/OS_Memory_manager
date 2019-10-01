#include "mmemory.h"
#include "adress_spaces.h"
#include "segment_table.h"
#include "unit_test.h"

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	size_t szPage = 100;
	uint n = 10;
	test_init(n, szPage);

	VA segment_starting_va1 = NULL;
	size_t size1 = 200;
	test_malloc(&segment_starting_va1, size1);

	_print_vas();
	_print_segment_table();

	test_free(segment_starting_va1);

	_print_vas();
	_print_segment_table();

	return 0;
}
