#include "adress_spaces.h"
#include "segment_table.h"
#include "mmemory.h"
#include "unit_test.h"

#include <assert.h>
#include <stdlib.h>

void init_testing_env()
{
	out_ptr = (VA)malloc(sizeof(VA));
	freed_seg_starting_adress = (VA**)malloc(sizeof(VA*));
	*freed_seg_starting_adress = (VA*)malloc(sizeof(VA));
}

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
	size = _vas_size;
	for (uint rec_index = 0; _segment_table->records[rec_index].segment_ptr != NULL && size >= 0; rec_index++)
	{
		size = size - _segment_table->records[rec_index].segment_ptr->size;
	}
	size -= size / 2;

	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _SUCCESS);
}

void test_malloc__wrong_params ()
{
	size = _vas_size + 1;

	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _WRONG_PARAMS);
}

void test_malloc__memory_lack ()
{
	size = _vas_size;
	for (uint rec_index = 0; _segment_table->records[rec_index].segment_ptr != NULL && size >= 0; rec_index++)
	{
		size = size - _segment_table->records[rec_index].segment_ptr->size;
	}
	size += 1;

	int malloc_return_code = _malloc(out_ptr, size);
	if (size != _vas_size + 1)
	{
		assert(malloc_return_code == _MEMORY_LACK);
	}
}

void test_malloc__unknown_err ()
{
	// ��� ��������� malloc() ������� null?
}

void test_free__success () {
	st_record* rec = &_segment_table->records[0];
	if (rec->segment_ptr != NULL) {
		VA rand_seg_starting_va = rec->segment_ptr->starting_va;

		size = rec->segment_ptr->size;
		*freed_seg_starting_adress = _vas + _adress_abs_offset(_vas, rand_seg_starting_va);

		int free_return_code = _free(rand_seg_starting_va);
		assert(free_return_code == _SUCCESS);
	}
	else
	{
		*freed_seg_starting_adress = NULL;
	}
}

void test_free__wrong_params () {
	VA* expected_seg_start_va = _first_null_content_adress(_vas, _vas, _last_free_va);
	if (expected_seg_start_va != NULL) {
		*freed_seg_starting_adress = expected_seg_start_va;

		int free_return_code = _free(expected_seg_start_va);
		assert(free_return_code == _WRONG_PARAMS);
	}
}

void test_free__unknown_err() {

}

