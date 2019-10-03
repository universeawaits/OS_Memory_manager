#include "adress_spaces.h"
#include "segment_table.h"

#include <stdio.h>
#include <stdlib.h>

int _init_pas(size_t size)
{
	if (size > _PAS_MAX_SIZE || size < 0 || size < _PAS_MIN_SIZE) return _WRONG_PARAMS;

	_pas = (PA*)malloc(sizeof(PA) * size);
	if (_pas == NULL) return _UNKNOWN_ERR;

	// Ёмул€ци€ зан€тости последних адресов _pas сегментной таблицей и тд
	_pas_size = size - _PAS_MIN_SIZE + 1;

	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_pas[adress_index] = NULL;
	}
	_first_free_pa = _pas;
	_last_free_pa = _pas + _pas_size;

	return _SUCCESS;
}

int _init_vas (size_t size)
{
	if (size > _VAS_MAX_SIZE || size < 0) return _WRONG_PARAMS;
	
	_vas = (VA*)malloc(sizeof(VA) * size);
	if (_vas == NULL) return _UNKNOWN_ERR;

	_vas_size = size;

	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		_vas[adress_index] = NULL;
	}
	_first_free_va = _vas;
	_last_free_va = _vas + _vas_size;

	return _SUCCESS;
}

uint _validate_pa (PA pa)
{
	for (uint adress_offset = 0; adress_offset < _pas_size; adress_offset++)
	{
		if (_pas[adress_offset] == pa) return adress_offset;
	}
	
	return _FORBIDDEN_ADRESS_OFFSET;
}

uint _validate_va (VA va)
{
	for (uint adress_offset = 0; adress_offset < _vas_size; adress_offset++)
	{
		if (_vas[adress_offset] == va) return adress_offset;
	}

	return _FORBIDDEN_ADRESS_OFFSET;
}

void _load_into_mem (segment* segment)
{
	uint curr_adress_offset = 0;
	while (curr_adress_offset < sizeof(char) * segment->size)
	{
		*(_first_free_pa + curr_adress_offset) = segment->starting_pa + curr_adress_offset;
		curr_adress_offset++;
	}

	_first_free_pa = _first_pa_with_null_content(_pas);
}

PA*	_request_free_pspace (size_t size)
{
	if (size == 0) return _pas;

	PA* starting_adress = _pas;
	size_t nulled_space_size = 0;
	while (starting_adress != NULL)
	{
 		nulled_space_size = _nulled_pspace_size(starting_adress);
		if (nulled_space_size >= size) return starting_adress;

		starting_adress++;
		starting_adress = _first_pa_with_null_content(starting_adress);
	}

	return NULL;
}

size_t _nulled_pspace_size (PA* starting_adress)
{
	if (starting_adress == NULL) starting_adress = _pas;

	PA* adress = starting_adress;
	size_t space_size = 0;
	while (*adress == NULL)
	{
		space_size++;
		adress++;
	}

	return space_size;
}

PA* _first_pa_with_null_content (PA* starting_adress)
{
	if (starting_adress == NULL) starting_adress = _pas;

	PA* starting_adress_copy = starting_adress;
	while (starting_adress_copy < _last_free_pa)
	{
		if (*starting_adress_copy == NULL) return starting_adress_copy;
		starting_adress_copy++;
	}

	return NULL;
}

void _unload_from_mem (segment* segment)
{
	uint curr_adress_offset = 0;
	PA* starting_adress_ptr = _pas + _validate_pa(segment->starting_pa);
	while (curr_adress_offset < sizeof(char) * segment->size)
	{
		*(starting_adress_ptr + curr_adress_offset) = NULL;
		curr_adress_offset++;
	}

	_mark_as_unloaded(segment);
}

void _load_adjacent_segments_into_mem (segment* central_segment)
{

}

VA* _request_free_vspace (size_t size)
{
	if (size == 0) return _vas;

	VA* starting_adress = _vas;
	size_t nulled_space_size = 0;
	while (starting_adress != NULL)
	{
		nulled_space_size = _nulled_vspace_size(starting_adress);
		if (nulled_space_size >= size) return starting_adress;

		starting_adress++;
		starting_adress = _first_va_with_null_content(starting_adress);
	}

	return NULL;
}

void _defragment_vas ()
{
	VA* starting_adress = _vas;
	size_t nulled_space_size = 0;
	while (starting_adress != NULL)
	{
		nulled_space_size = _nulled_vspace_size(starting_adress);
		_shift_vas_content_left(starting_adress, nulled_space_size);

		starting_adress++;
		starting_adress = _first_va_with_null_content(starting_adress);
	}
	_first_free_va = _first_va_with_null_content(_vas);
}

void _defragment_pas ()
{
	PA* starting_adress = _pas;
	size_t nulled_space_size = 0;
	while (starting_adress != NULL)
	{
		nulled_space_size = _nulled_pspace_size(starting_adress);
		_shift_pas_content_left(starting_adress, nulled_space_size);

		starting_adress++;
		starting_adress = _first_pa_with_null_content(starting_adress);
	}
	_first_free_pa = _first_pa_with_null_content(_pas);
}

size_t _nulled_vspace_size (VA* starting_adress)
{
	if (starting_adress == NULL) starting_adress = _vas;

	VA* adress = starting_adress;
	size_t space_size = 0;
	while (*adress == NULL)
	{
		space_size++;
		adress++;
	}

	return space_size;
}

VA* _first_va_with_null_content (VA* starting_adress)
{
	if (starting_adress == NULL) starting_adress = _vas;
	VA* starting_adress_copy = starting_adress;

	while (starting_adress_copy < _last_free_va)
	{
		if (*starting_adress_copy == NULL) return starting_adress_copy;
		starting_adress_copy++;
	}

	return NULL;
}

void _shift_vas_content_left (VA* starting_adress, uint offset)
{
	if (offset == 0) return;

	VA* adress = starting_adress;
	while (adress < _last_free_va - offset)
	{
		*adress = *(adress + offset);
		*(adress + offset) = NULL;
		adress++;
	}
}

void _shift_pas_content_left (PA* starting_adress, uint offset)
{
	if (offset == 0) return;

	PA* adress = starting_adress;
	while (adress < _last_free_pa - offset)
	{
		*adress = *(adress + offset);
		*(adress + offset) = NULL;
		adress++;
	}
}



int	_organize_pspace_for_segment_allocation(size_t size)
{
	if (_first_free_pa + size > _last_free_pa)
	{
		_first_free_pa = _request_free_pspace(size);
		if ((_first_free_pa == NULL) || _first_free_pa + size > _last_free_pa)
		{
			_defragment_pas();
			if ((_first_free_pa == NULL) || _first_free_pa + size > _last_free_pa)
			{
				return _MEMORY_LACK;
			}
		}
	}

	return _SUCCESS;
}

int _organize_vspace_for_segment_allocation (size_t size)
{
	if (_first_free_va + size > _last_free_va)
	{
		_first_free_va = _request_free_vspace(size);
		if ((_first_free_va == NULL) || _first_free_va + size > _last_free_va)
		{
			_defragment_vas();
			if ((_first_free_va == NULL) || _first_free_va + size > _last_free_va)
			{
				return _MEMORY_LACK;
			}
		}
	}

	return _SUCCESS;
}

int	_init_first_free_adress (size_t content_size)
{
	*_first_free_va = (VA)malloc(sizeof(VA) * content_size);
	*_first_free_pa = (PA)malloc(sizeof(PA) * content_size);
	if (*_first_free_va == NULL || *_first_free_pa == NULL) return _UNKNOWN_ERR;

	return _SUCCESS;
}

int _allocate_segment (size_t size)
{
	VA vsegment_space = (VA)malloc(sizeof(char) * size);
	PA psegment_space = (PA)malloc(sizeof(char) * size);
	if (vsegment_space == NULL || psegment_space == NULL) return _UNKNOWN_ERR;

	uint curr_adress_offset = 0;
	while (curr_adress_offset < size)
	{
		*(_first_free_va + curr_adress_offset) = vsegment_space + curr_adress_offset;
		*(_first_free_pa + curr_adress_offset) = psegment_space + curr_adress_offset;
		curr_adress_offset++;
	}

	return _SUCCESS;
}

int	_register_segment (segment* segment)
{
	int add_rec_return_code = _add_record_to_segment_table(segment);
	return add_rec_return_code;
}

void _renew_first_free_adress (size_t prob_null_adress_offset)
{
#define OFFSET prob_null_adress_offset
	if (*(_first_free_va + OFFSET) == NULL) _first_free_va += OFFSET;
	else _first_free_va = _first_va_with_null_content(_vas);

	if (*(_first_free_pa + OFFSET) == NULL) _first_free_pa += OFFSET;
	else _first_free_pa = _first_pa_with_null_content(_pas);
#undef OFFSET
}


void _print_vas()
{
	printf("\n -------------------------------\n");
	printf("| Virtual adress space\t\t|");
	printf("\n -------------------------------\n");
	printf("| Adress\t| Content\t|");
	printf("\n -------------------------------\n");

	for (uint adress_offset = 0; adress_offset < _vas_size; adress_offset++)
	{
		printf("| %p\t| %c\t\t|\n", *(_vas + adress_offset), _vas[adress_offset] == NULL ? ' ' : *_vas[adress_offset]);
	}

	printf(" -------------------------------\n");
}

void _print_pas()
{
	printf("\n -------------------------------\n");
	printf("| Physical adress space\t\t|");
	printf("\n -------------------------------\n");
	printf("| Adress\t| Content\t|");
	printf("\n -------------------------------\n");

	for (uint adress_offset = 0; adress_offset < _pas_size; adress_offset++)
	{
		printf("| %p\t| %c\t\t|\n", *(_pas + adress_offset), _pas[adress_offset] == NULL ? ' ' : *_pas[adress_offset]);
	}

	printf(" -------------------------------\n");
}