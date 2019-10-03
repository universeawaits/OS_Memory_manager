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

	VA s1 = NULL;
	size_t size = 2;
	test_malloc(&s1, size);

	VA s2 = NULL;
	size = 1;
	test_malloc(&s2, size);

	VA s3 = NULL;
	size = 3;
	test_malloc(&s3, size);

	test_free(s2);

	VA s4 = NULL;
	size = 44;
	test_malloc(&s4, size);

	test_free(s4);

	VA s5 = NULL;
	size = 12;
	test_malloc(&s5, size);

	VA s6 = NULL;
	size = 232;
	test_malloc(&s6, size);

	_print_vas();
	_print_pas();
	_print_segment_table();

	return 0;
}
