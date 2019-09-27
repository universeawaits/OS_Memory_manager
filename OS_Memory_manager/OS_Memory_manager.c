#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdio.h>

#define _SUCCESS 0
#define _WRONG_PARAMS -1
#define _MEMORY_LACK -2
#define _UNKNOWN_ERR 1

int main ()
{
	if (_init(10, 100) == _SUCCESS)
	{
		_print_pas();
		_print_vas();
		_print_segment_table();
	}
	else
	{
		printf("Error");
	}
}
