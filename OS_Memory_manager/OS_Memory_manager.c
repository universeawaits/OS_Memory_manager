#include "mmemory.h"
#include "adress_spaces.h"
#include "segment_table.h"
#include "unit_test.h"

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	size_t szPage = 5;
	uint n = 100;
	test_init(szPage, n);
	_print_space(_vas, 10, "Virtual adress space");

	VA s1 = NULL;
	size_t size = 1;
	test_malloc(&s1, size);
	_print_space(_vas, 10, "Virtual adress space");

	VA s2 = NULL;
	size = 2;
	test_malloc(&s2, size);
	_print_space(_vas, 10, "Virtual adress space");

	VA s3 = NULL;
	size = 3;
	test_malloc(&s3, size);
	_print_space(_vas, 10, "Virtual adress space");

	test_free(s2);
	_print_space(_vas, 10, "Virtual adress space");

	VA s5 = NULL;
	size = 230;
	test_malloc(&s5, size);
	_print_space(_vas, _vas_size, "Virtual adress space");

	VA s6 = NULL;
	size = 265;
	test_malloc(&s6, size);
	_print_space(_vas, _vas_size, "Virtual adress space");

	_print_segment_table();

	return 0;
}
