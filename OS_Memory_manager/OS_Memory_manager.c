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

	VA segment_starting_va_ptr = NULL;
	size_t size = 12;
	test_malloc(&segment_starting_va_ptr, size);

	return 0;
}
