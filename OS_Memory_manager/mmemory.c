#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h> 

int _malloc (VA* ptr, size_t szBlock)
{
	if (_first_free_va + szBlock > _last_free_va)
	{
		_defragment_vas();

		if (_first_free_va + szBlock > _last_free_va)
		{
			return _MEMORY_LACK;
		}
	}
	*ptr = _first_free_va;

	return _SUCCESS;
}

int _free(VA ptr) 
{
	if (ptr == NULL || _validate_va(ptr) == NULL || _find_segment(ptr))
	{
		return _WRONG_PARAMS;
	}

	ptr = NULL;
	return _SUCCESS;
}

int _read(VA ptr, void* pBuffer, size_t szBuffer) 
{

	return _SUCCESS;
}

int _write(VA ptr, void* pBuffer, size_t szBuffer) 
{

	return _SUCCESS;
}

int _init(int n, int szPage) 
{
	if (_init_pas(n * szPage) == _WRONG_PARAMS)
	{
		return _WRONG_PARAMS;
	}

	if (_init_vas(n * szPage) == _WRONG_PARAMS)
	{
		return _WRONG_PARAMS;
	}

	_init_segment_table();

	return _SUCCESS;
}
