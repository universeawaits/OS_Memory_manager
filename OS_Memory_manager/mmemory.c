#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

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

	segment* new_segment = (segment*)malloc(sizeof(segment));
	if (new_segment == NULL)
	{
		return _UNKNOWN_ERR;
	}

	*_first_free_va = (VA)malloc(sizeof(VA) * szBlock);
	if (*_first_free_va == NULL)
	{
		return _UNKNOWN_ERR;
	}

	new_segment->size = szBlock;
	new_segment->starting_va = *_first_free_va;

	int add_rec_return_code = _add_record_to_segment_table(new_segment);
	if (add_rec_return_code != _SUCCESS)
	{
		return add_rec_return_code;
	}

	VA segment_space = (VA)malloc(sizeof(char) * szBlock);

	uint curr_adress_offset = 0;
	while (curr_adress_offset < szBlock)
	{
		*(_first_free_va + curr_adress_offset) = segment_space + curr_adress_offset;
		curr_adress_offset++;
	}

	*ptr = *_first_free_va;
	_first_free_va += szBlock;

	return _SUCCESS;
}

int _free (VA ptr) 
{
	if (ptr == NULL ||
		_validate_va(ptr) == _FORBIDDEN_ADRESS ||
		_find_segment(ptr) == NULL)
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
	int init_pas_return_code = _init_pas(n * szPage);
	if (init_pas_return_code != _SUCCESS)
	{
		return init_pas_return_code;
	}

	int init_vas_return_code = _init_vas(n * szPage);
	if (init_vas_return_code != _SUCCESS)
	{
		return init_vas_return_code;
	}

	int init_st_return_code = _init_segment_table();
	if (init_st_return_code != _SUCCESS) {
		return init_st_return_code;
	}

	return _SUCCESS;
}
