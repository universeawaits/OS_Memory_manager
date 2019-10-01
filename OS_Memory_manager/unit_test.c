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