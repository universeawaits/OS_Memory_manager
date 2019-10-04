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
	size_t size = 1;
	test_malloc(&s1, size);

	VA s2 = NULL;
	size = 2;
	test_malloc(&s2, size);

	VA s3 = NULL;
	size = 3;
	test_malloc(&s3, size);

	test_free(s2);

	VA s5 = NULL;
	size = 230;
	test_malloc(&s5, size);

	VA s6 = NULL;
	size = 266;
	test_malloc(&s6, size);
	_print_space(_vas, _vas_size, "Virtual adress space");
	_print_segment_table();

	*s5 = 'a';
	*(s5 + 1) = 'b';
	_print_space(_vas, _vas_size, "Virtual adress space");
	VA buffer = (VA)malloc(sizeof(*buffer) * 2);
	test_read(s5, buffer, 2);
	printf("%c%c", *(char*)buffer, *((char*)buffer + 1));

	return 0;
}
