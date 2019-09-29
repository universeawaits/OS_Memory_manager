#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdio.h>
#include <stdlib.h>

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
		printf("Error initializing memory\n");
	}

	VA first_segment_exapmle = NULL;
	size_t segment_size = 10;
	if (_malloc(&first_segment_exapmle, segment_size) == _SUCCESS)
	{
		printf("First example segment starting VA: %p", first_segment_exapmle);
	}

	/*VA* vas = (VA*)malloc(sizeof(VA) * 10);
	VA vas_content = (VA)malloc(10);

	for (int i = 0; i < 10; i++) {
		vas_content[i] = 's';
		vas[i] = vas_content[i];
		printf("vas: %p; vas_content: %p, char: %c\n", vas[i], vas_content + i, vas_content[i]);
	}*/
}
