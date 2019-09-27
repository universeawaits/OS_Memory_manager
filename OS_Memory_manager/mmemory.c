#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdlib.h>
#include <stdbool.h>

int _malloc (VA* ptr, size_t szBlock)
{
	if (_first_free_va_index == _NULL_MEMORY_INDEX)
	{
		_defragment_vas ();

		if (_first_free_va_index == _NULL_MEMORY_INDEX)
		{
			return _MEMORY_LACK;
		}
	}

	return _SUCCESS;
}

int _free(VA ptr) 
{
	if (ptr == NULL || _validate_va(ptr) == NULL) 
	{
		return _WRONG_PARAMS;
	}

	ptr = NULL;
	return _SUCCESS;
}

int _read(VA ptr, void* pBuffer, size_t szBuffer) 
{

}

int _write(VA ptr, void* pBuffer, size_t szBuffer) 
{

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