#include "adress_spaces.h"
#include "segment_table.h"
#include "unit_test.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>


size_t pgSize = 1000;
uint n = 100;

size_t malloc_size;
VA* malloc_ptr;

size_t freed_size;
VA* freed_ptr;

size_t write_buffer_size;
VA* write_buffer;
VA* written_adress;

size_t read_buffer_size;
VA* read_buffer;
VA* read_adress;

void init_unit_testing_env()
{
	assert(_init(n, pgSize) == _SUCCESS);

	malloc_ptr = (VA*)malloc(sizeof(VA));
	freed_ptr = (VA*)malloc(sizeof(VA));

	write_buffer = (VA*)malloc(sizeof(VA));
	written_adress = (VA*)malloc(sizeof(VA));

	read_buffer = (VA*)malloc(sizeof(VA));
	read_adress = (VA*)malloc(sizeof(VA));
}

void test_malloc__success()
{
	malloc_size = n * pgSize / 1000;

	int return_code = _malloc(malloc_ptr, malloc_size);
	assert(return_code == _SUCCESS);
}

void test_malloc__wrong_params()
{
	malloc_size = _pas_size + 1;

	int return_code = _malloc(malloc_ptr, malloc_size);
	assert(return_code == _WRONG_PARAMS);
}

void test_malloc__memory_lack()
{
	malloc_size = n * pgSize / 2;
	_malloc(malloc_ptr, malloc_size);
	malloc_size = _pas_size - 2;

	int return_code = _malloc(malloc_ptr, malloc_size);
	assert(return_code == _MEMORY_LACK);
}

void test_free__success()
{
	malloc_size = n * pgSize / 100;
	_malloc(malloc_ptr, malloc_size);

	int return_code = _free(*malloc_ptr);
	assert(return_code == _SUCCESS);

	freed_ptr = malloc_ptr;
	freed_size = malloc_size;
}

void test_free_wrong_params()
{
	malloc_size = n * pgSize / 100;
	_malloc(malloc_ptr, malloc_size);

	*malloc_ptr = NULL;

	int return_code = _free(*malloc_ptr);
	assert(return_code == _WRONG_PARAMS);

	freed_ptr = malloc_ptr;
	freed_size = malloc_size;
}

void test_write__success()
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = segment->starting_va;

	write_buffer_size = segment->size;
	*write_buffer = (VA)malloc(write_buffer_size);

	for (uint i = 0; i < write_buffer_size; i++)
	{
		*(*write_buffer + i) = '1' + i;
	}

	int return_code = _write(segment_starting_adress, *write_buffer, write_buffer_size);
	assert(return_code == _SUCCESS && memcmp(
		segment_starting_adress,
		*write_buffer,
		write_buffer_size
	) == 0);

	*written_adress = segment_starting_adress;
}

void test_write__wrong_params()
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = *_vas;

	write_buffer_size = segment->size;
	*write_buffer = (VA)malloc(write_buffer_size);

	for (uint i = 0; i < write_buffer_size; i++)
	{
		*(*write_buffer + i) = i + 42;
	}

	int return_code = _write(segment_starting_adress - 1, *write_buffer, write_buffer_size);
	assert(return_code == _WRONG_PARAMS);

	*written_adress = NULL;
}

void test_write__segment_access_violation() 
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = segment->starting_va;

	write_buffer_size = segment->size + 1;
	*write_buffer = (VA)malloc(write_buffer_size);

	for (uint i = 0; i < write_buffer_size; i++)
	{
		*(*write_buffer + i) = i + 42;
	}

	int return_code = _write(segment_starting_adress, *write_buffer, write_buffer_size);
	assert(return_code == _SEGMENT_ACCESS_VIOLATION);

	*written_adress = NULL;
}

void test_read__success() 
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = segment->starting_va;

	read_buffer_size = segment->size;
	*read_buffer = (VA)malloc(read_buffer_size);

	int return_code = _read(segment_starting_adress, *read_buffer, read_buffer_size);
	assert(return_code == _SUCCESS && memcmp(
		segment_starting_adress,
		*read_buffer,
		read_buffer_size
	) == 0);

	*read_adress = segment_starting_adress;
}

void test_read__wrong_params() 
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = *_vas;

	read_buffer_size = segment->size;
	*read_buffer = (VA)malloc(read_buffer_size);

	int return_code = _read(segment_starting_adress - 1, *read_buffer, read_buffer_size);
	assert(return_code == _WRONG_PARAMS);

	*read_adress = NULL;
}

void test_read__segment_access_violation() 
{
	segment* segment = _segment_table->records[0].segment_ptr;
	VA segment_starting_adress = segment->starting_va;

	read_buffer_size = segment->size + 1;
	*read_buffer = (VA)malloc(read_buffer_size);

	int return_code = _read(segment_starting_adress, *read_buffer, read_buffer_size);
	assert(return_code == _SEGMENT_ACCESS_VIOLATION);

	*read_adress = NULL;
}

void print_malloc_results()
{
	printf("\nPASSED: ");
	if (*malloc_ptr != NULL)
	{
		printf("Allocated memory size was %d, adress (VA) was %p", malloc_size, *malloc_ptr);
	}
	else
	{
		printf("Allocated memory size may be %d, but there is no enough free space", malloc_size);
	}
}

void print_free_results()
{
	printf("\nPASSED: ");
	if (*freed_ptr != NULL)
	{
		printf("Freed memory size was %d, adress (VA) was %p", freed_size, *freed_ptr);
	}
	else
	{
		printf("Freed memory size may be %d, but there is no such adress (VA) %p", freed_size, *freed_ptr);
	}
}

void print_write_results() 
{
	printf("\nPASSED: ");
	if (*written_adress != NULL)
	{
		*(*write_buffer + write_buffer_size) = '\0';
		printf("Written buffer size was %d, adress (VA) was %p, buffer was %s", 
			write_buffer_size,
			*written_adress, 
			*write_buffer);
	}
	else
	{
		printf("Written memory size may be %d, but is are no such adress or segmentation fault occured", write_buffer_size);
	}
}

void print_read_results() 
{
	printf("\nPASSED: ");
	if (*read_adress != NULL)
	{
		*(*read_buffer + read_buffer_size) = '\0';
		printf("Read buffer size was %d, adress (VA) was %p, buffer is %s",
			read_buffer_size,
			*read_adress,
			*read_buffer);
	}
	else
	{
		printf("Read memory size may be %d, but is are no such adress or segmentation fault occured", read_buffer_size);
	}
}


void run_all_unit_tests()
{
	test_malloc__success();
	print_malloc_results();

	test_malloc__wrong_params();
	print_malloc_results();

	test_malloc__memory_lack();
	print_malloc_results();
	printf("\n");

	test_free__success();
	print_free_results();

	test_free_wrong_params();
	print_free_results();
	printf("\n");

	test_write__success();
	print_write_results();

	test_write__wrong_params();
	print_write_results();

	test_write__segment_access_violation();
	print_write_results();
	printf("\n");

	test_read__success();
	print_read_results();

	test_read__wrong_params();
	print_read_results();

	test_read__segment_access_violation();
	print_read_results();
}