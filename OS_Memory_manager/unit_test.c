#include "adress_spaces.h"
#include "segment_table.h"
#include "mmemory.h"
#include "unit_test.h"

#include <assert.h>

void test_init__success ()
{
	szPage	= 50;
	n		= 10;

	int init_return_code = _init(n, szPage);
	assert(init_return_code == _SUCCESS);
}

void test_init__wrong_params ()
{
	szPage	= 1024;
	n		= 11;

	int init_return_code = _init(n, szPage);
	assert(init_return_code == _WRONG_PARAMS);
}

void test_init__unknown_err ()
{
	// ��� ��������� malloc() ������� null?
}

void test_malloc__success ()
{
	out_ptr = (VA)malloc(sizeof(VA));
	size = _vas_size;
	for (uint rec_index = 0; _segment_table->records[rec_index].segment_ptr != NULL; rec_index++)
	{
		size = -_segment_table->records[rec_index].segment_ptr->size;
	}

	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _SUCCESS);
}

void test_malloc__wrong_params ()
{
	out_ptr = (VA)malloc(sizeof(VA));
	size = _vas_size;

	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _SUCCESS);
}

void test_malloc__memory_lack ()
{
	out_ptr = (VA)malloc(sizeof(VA));
	size = _vas_size;
	for (uint rec_index = 0; _segment_table->records[rec_index].segment_ptr != NULL; rec_index++)
	{
		size = -_segment_table->records[rec_index].segment_ptr->size;
	}
	size += 1;

	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _SUCCESS);
}

void test_malloc__unknown_err ()
{

}
