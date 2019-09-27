#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdio.h>

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
