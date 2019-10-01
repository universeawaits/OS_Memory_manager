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
	size_t size1 = 12;
	test_malloc(&segment_starting_va1, size1);

	_print_vas();
	_print_segment_table();

	VA segment_starting_va2 = NULL;
	size_t size2 = 5;
	test_malloc(&segment_starting_va2, size2);

	VA segment_starting_va3 = NULL;
	size_t size3 = 100;
	test_malloc(&segment_starting_va3, size3);

	VA segment_starting_va4 = NULL;
	size_t size4 = 2;
	test_malloc(&segment_starting_va4, size4);

	VA segment_starting_va5 = NULL;
	size_t size5 = 600;
	test_malloc(&segment_starting_va5, size5);

	_print_vas();
	_print_segment_table();

	return 0;
}
