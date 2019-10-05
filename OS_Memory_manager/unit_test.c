#include "adress_spaces.h"
#include "mmemory.h"
#include "unit_test.h"

#include <assert.h>

void test_init (int n, int szPage)
{
	assert(_init(n, szPage) == _SUCCESS);
}

void test_malloc (VA* out_ptr, size_t size)
{
	int malloc_return_code = _malloc(out_ptr, size);
	assert(malloc_return_code == _SUCCESS);
}

void test_free (VA segment_starting_va)
{
	int free_return_code = _free(segment_starting_va);
	assert(free_return_code == _SUCCESS);
}

void test_read (VA ptr, void* pBuffer, size_t szBuffer)
{
	int read_return_code = _read(ptr, pBuffer, szBuffer);
	assert(read_return_code == _SUCCESS);
}

void test_write (VA ptr, void* pBuffer, size_t szBuffer)
{
	int write_return_code = _write(ptr, pBuffer, szBuffer);
	assert(write_return_code == _SUCCESS);
}

void test_init__success ()
{
	int szPage	= 50;
	int n		= 10;

	int init_return_code = _init(n, szPage);
	assert(init_return_code == _SUCCESS);
}

void test_init__wrong_params ()
{
	int szPage = 1024;
	int n = 11;

	int init_return_code = _init(n, szPage);
	assert(init_return_code == _WRONG_PARAMS);
}

void test_init__unknown_err ()
{

}
