#include "mmemory.h"
#include "adress_spaces.h"
#include "segment_table.h"
#include "unit_test.h"

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	size_t szPage = 5;
	uint n = 30;
	test_init(szPage, n);

	VA s2 = NULL;
	size_t size = 2;
	test_malloc(&s2, size);

	VA s1 = NULL;
	size = 3;
	test_malloc(&s1, size);

	VA s3 = NULL;
	size = 1;
	test_malloc(&s3, size);
	_print_space(_vas, 8, "Virtual adress space");
	_print_space(_pas, 8, "Physical adress space");
	_print_segment_table();

	VA buffer = (VA)malloc(sizeof(*buffer) * 2);
	*buffer = 'a';
	*(buffer + 1) = 'b';
	test_write(s1, buffer, 2);

	_print_space(_vas, 8, "Virtual adress space");
	_print_space(_pas, 8, "Physical adress space");
	_print_segment_table();
	printf("%c%c", *(char*)s1, *((char*)s1 + 1));

	return 0;
}
