#include "mmemory.h"
#include "adress_spaces.h"
#include "segment_table.h"
#include "unit_test.h"

#include <stdio.h>
#include <stdlib.h>

int main ()
{
	VA* d = (VA)malloc(1);
	_init(10, 300);
	_malloc(d, 10);

	_print_space(_vas, 10, "fds");

	return 0;
}
