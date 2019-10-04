#include "adress_spaces.h"
#include "segment_table.h"

#include <stdio.h>
#include <stdlib.h>

int _init_pas(size_t size)
{
	if (size > _PAS_MAX_SIZE || size < 0 || size < _PAS_MIN_SIZE) return _WRONG_PARAMS;

	_pas = (VA*)malloc(sizeof(VA) * size);
	if (_pas == NULL) return _UNKNOWN_ERR;

	// Ёмул€ци€ зан€тости последних адресов _pas сегментной таблицей и тд
	_pas_size = size - _PAS_MIN_SIZE;
	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_pas[adress_index] = NULL;
	}
	_first_free_pa = _pas;
	_last_free_pa = _pas + _pas_size;
	*_last_free_pa = NULL;

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
	_last_free_va = _vas + _vas_size - 1;
	*_last_free_va = NULL;

	return _SUCCESS;
}

uint _adress_abs_offset (VA* space, VA adress)
{
	for (uint adress_offset = 0; adress_offset < _vas_size; adress_offset++)
	{
		if (_vas[adress_offset] == adress) return adress_offset;
	}

	return _FORBIDDEN_ADRESS_OFFSET;
}

VA*	_request_free_space_region (VA* space, VA* last_free_space_adress, size_t size)
{
	if (size == 0) return space;

	VA* starting_adress = space;
	size_t nulled_space_size = 0;
	while (starting_adress != NULL)
	{
 		nulled_space_size = _nulled_space_region_size(space, starting_adress);
		if (nulled_space_size >= size) return starting_adress;

		starting_adress++;
		starting_adress = _first_null_content_adress(space, starting_adress, last_free_space_adress);
	}

	return NULL;
}

size_t _nulled_space_region_size (VA* space, VA* space_region)
{
	if (space_region == NULL) space_region = space;

	VA* adress = space_region;
	size_t space_size = 0;
	while (*adress == NULL)
	{
		space_size++;
		adress++;
	}

	return space_size;
}

void _unload_from_mem (segment* segment)
{
	uint curr_adress_offset = 0;
	VA* starting_adress_ptr = _pas + _adress_abs_offset(_pas, segment->starting_pa);
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

VA* _defragment_space (VA* space, VA* last_free_space_adress)
{
	VA* starting_adress = space;
	size_t nulled_space_region_size = 0;
	while (starting_adress != NULL)
	{
		nulled_space_region_size = _nulled_space_region_size(_vas, starting_adress);
		_shift_space_content_left(starting_adress, _last_free_va, nulled_space_region_size);

		starting_adress++;
		starting_adress = _first_null_content_adress(
			space, starting_adress, last_free_space_adress
			);
	}
	_print_space(_vas, _vas_size, "v");
	return _first_null_content_adress(space, space, last_free_space_adress);
}

VA* _first_null_content_adress (VA* space, VA* starting_adress, VA* last_free_space_adress)
{
	if (starting_adress == NULL) starting_adress = space;
	VA* starting_adress_copy = starting_adress;

	while (starting_adress_copy <= last_free_space_adress)
	{
		if (*starting_adress_copy == NULL) return starting_adress_copy;
		starting_adress_copy++;
	}

	return NULL;
}

void _shift_space_content_left (VA* starting_adress, VA* last_free_space_adress, uint offset)
{
	if (offset == 0) return;

	VA* adress = starting_adress;
	while (adress <= last_free_space_adress - offset)
	{
		*adress = *(adress + offset);
		*(adress + offset) = NULL;
		adress++;
	}
}

int	_organize_space_for_segment_allocation (
	VA* space,
	VA** first_free_space_adress, 
	VA* last_free_space_adress, 
	size_t segment_size
	)
{
#define SIZE segment_size
#define FIRST first_free_space_adress
#define LAST last_free_space_adress

	if (*FIRST + SIZE > LAST)
	{
		*first_free_space_adress = _request_free_space_region(space, last_free_space_adress, SIZE);
		if ((*FIRST == NULL) ||
			*FIRST + SIZE > LAST)
		{
			*first_free_space_adress = _defragment_space(space, last_free_space_adress);

			if ((*FIRST == NULL) ||
				*FIRST + SIZE > LAST + 1) return _MEMORY_LACK;
		}
	}

	return _SUCCESS;

#undef SIZE
#undef FIRST
#undef LAST
}

int	_init_adress (VA* adress, size_t content_size)
{
	*adress = (VA)malloc(sizeof(VA) * content_size);
	return (*adress == NULL) ? _UNKNOWN_ERR : _SUCCESS;
}

int _allocate_segment (VA* allocating_adress, size_t size)
{
	VA vsegment_space = (VA)malloc(sizeof(char) * size);
	if (vsegment_space == NULL) return _UNKNOWN_ERR;

	uint curr_adress_offset = 0;
	while (curr_adress_offset < size)
	{
		*(allocating_adress + curr_adress_offset) = vsegment_space + curr_adress_offset;
		curr_adress_offset++;
	}

	return _SUCCESS;
}

int	_register_segment (segment* segment)
{
	int add_rec_return_code = _add_record_to_segment_table(segment);
	return add_rec_return_code;
}


void _print_space (VA* space, size_t adress_offset_limit, const char* space_name)
{
	printf("\n -------------------------------\n");
	printf("| "); 
	printf(space_name);
	printf("\t\t|");
	printf("\n -------------------------------\n");

	printf("| Adress\t| Content\t|");
	printf("\n -------------------------------\n");

	for (uint offset = 0; offset < adress_offset_limit; offset++)
	{
		printf("%p| %p\t| %c\t\t|\n", space + offset, *(space + offset), space[offset] == NULL ? ' ' : *space[offset]);
	}

	printf(" -------------------------------\n");
}