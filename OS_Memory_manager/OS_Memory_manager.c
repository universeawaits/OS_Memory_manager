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
	_print_space(_vas, 4, "Virtual adress space");
	_print_space(_pas, 4, "Physical adress space");
	_print_segment_table();

	VA s1 = NULL;
	size_t size = 3;
	test_malloc(&s1, size);

	_print_space(_vas, 4, "Virtual adress space");
	_print_space(_pas, 4, "Physical adress space");
	_print_segment_table();

	VA buffer = (VA)malloc(sizeof(*buffer) * 2);
	test_read(s1, buffer, 2);

	_print_space(_vas, 4, "Virtual adress space");
	_print_space(_pas, 4, "Physical adress space");
	_print_segment_table();
	printf("%c%c", *(char*)buffer, *((char*)buffer + 1));

	return 0;
}
