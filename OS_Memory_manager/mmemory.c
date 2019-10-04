#include "mmemory.h"
#include "segment_table.h"
#include "adress_spaces.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

int _malloc (VA* ptr, size_t szBlock)
{
	if (szBlock <= 0 || (szBlock >= _pas_size - _PAS_MIN_SIZE) || ptr == NULL)
	{
		return _WRONG_PARAMS;
	}
	
	int return_code = 0;
	return_code		= _organize_space_for_segment_allocation (
		_vas, &_first_free_va, _last_free_va, szBlock
		);
	if (return_code != _SUCCESS) return return_code;

	return_code = _init_adress (_first_free_va, szBlock);
	if (return_code != _SUCCESS) return return_code;

	return_code = _allocate_segment (_first_free_va, szBlock);
	if (return_code != _SUCCESS) return return_code;
	 
	*ptr = *_first_free_va;
	segment* new_segment = (segment*)malloc(sizeof(segment));
	if (new_segment == NULL) return _UNKNOWN_ERR;

	new_segment->size			= szBlock;
	new_segment->starting_va	= *ptr;
	new_segment->starting_pa	= *_first_free_pa;

	return_code = _register_segment(new_segment);
	if (return_code != _SUCCESS) return return_code;

	if (*(_first_free_va + szBlock) == NULL) _first_free_va += szBlock;
	else _first_free_va = _first_null_content_adress(_vas, _vas, _last_free_va);

	return _SUCCESS;
}

int _free (VA ptr)
{
	if (ptr == NULL) return _WRONG_PARAMS;

	segment* found_segment = _find_segment(ptr);
	if (found_segment == NULL) return _WRONG_PARAMS;

	_clear_space_region(
		_pas + _adress_abs_offset(_pas, found_segment->starting_pa), 
		found_segment->size
		);
	_clear_space_region(
		_vas + _adress_abs_offset(_vas, found_segment->starting_va),
		found_segment->size
		);
	_remove_record_from_segment_table(found_segment);

	return _SUCCESS;
}

int _read(VA ptr, void* pBuffer, size_t szBuffer) 
{
	if (ptr == NULL || szBuffer <= 0) return _WRONG_PARAMS;

	uint ptr_offset = _adress_abs_offset(_vas, ptr);
	if (ptr_offset == _FORBIDDEN_ADRESS_OFFSET) return _WRONG_PARAMS;

	segment* owner = _find_segment_by_inner_adress (ptr, szBuffer);
	if (owner == NULL) return _WRONG_PARAMS;

	memcpy(pBuffer, ptr, szBuffer);

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
