#include "adress_spaces.h"
#include "segment_table.h"

#include <stdio.h>
#include <stdlib.h>

int _init_pas(size_t size)
{
	if (size > _PAS_MAX_SIZE || size < 0 || size < _PAS_MIN_SIZE) return _WRONG_PARAMS;

	_pas = (VA*)malloc(sizeof(VA) * size);
	if (_pas == NULL) return _UNKNOWN_ERR;

	// �������� ��������� ��������� ������� _pas ���������� �������� � ��
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

int _load_segment (segment* segment)
{
	int return_code = 0;
	return_code = _organize_space_for_segment_allocation(
		_pas, &_first_free_pa, _last_free_pa, segment->size
	);
	if (return_code == _MEMORY_LACK)
	{
		return_code = _unload_segments_to_free_space(segment->size);
		if (return_code != _SUCCESS) return return_code;
	}

	return_code = _init_adress(_first_free_pa, segment->size);
	if (return_code != _SUCCESS) return return_code;

	return_code = _allocate_segment(_first_free_pa, segment->size);
	if (return_code != _SUCCESS) return return_code;

	segment->starting_pa = *_first_free_pa;
	_change_loading_mark(segment, true);

	if (*(_first_free_pa + segment->size) == NULL) _first_free_pa += segment->size;
	else _first_free_pa = _first_null_content_adress(_pas, _pas, _last_free_pa);

	return _SUCCESS;
}

void _unload_segment (segment* segment)
{
	_clear_space_region (&segment->starting_pa, segment->size);
	_change_loading_mark (segment, false);
}

void _clear_space_region (VA* starting_adress, size_t size)
{
	if (starting_adress == NULL || *starting_adress == NULL) return;

	uint curr_adress_offset = 0;
	while (curr_adress_offset < sizeof(**(starting_adress)) * size)
	{
		*(starting_adress + curr_adress_offset) = NULL;
		curr_adress_offset++;
	}
}

int _load_adjacent_segments (segment* central_segment)
{
	if (central_segment->starting_va != *_vas)
	{
		VA* left_adj_seg = _vas + _adress_abs_offset(
			_vas,
			central_segment->starting_va // ������ +1?
		) - 1;; 
		while (*left_adj_seg == NULL)
		{
			left_adj_seg--;
		}
		if (++left_adj_seg != _vas)
		{
			segment* left_seg = _find_segment_by_inner_adress(*left_adj_seg, 0);
			if (left_seg == NULL) return _UNKNOWN_ERR;

			if (_find_record(left_seg)->is_loaded == false) _load_segment(left_seg);
		}
	}

	if (central_segment->starting_va + central_segment->size != *_last_free_va) 
	{
		VA* right_adj_seg = _vas + _adress_abs_offset(
			_vas,
			central_segment->starting_va 
			) + central_segment->size;
		while (*right_adj_seg == NULL)
		{
			right_adj_seg++;
		}
		if (--right_adj_seg != _last_free_va)
		{
			segment* right_seg = _find_segment_by_inner_adress(*right_adj_seg, 0);
			if (right_seg == NULL) return _UNKNOWN_ERR;

			if (_find_record(right_seg)->is_loaded == false) _load_segment(right_seg);
		}		
	}

	return _SUCCESS;
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

int _unload_segments_to_free_space (size_t space_region_size)
{
	while (_count_of_loaded_segments > 0)
	{
		_unload_random_segment();
		*_first_free_pa = _defragment_space(_pas, _last_free_pa);

		*_first_free_pa = _request_free_space_region(_pas, _last_free_pa, space_region_size);
		if (*_first_free_pa != NULL)
		{
			return _SUCCESS;
		}
	}

	return _MEMORY_LACK;
}

void _unload_random_segment ()
{
	for (uint rec_index = 0; rec_index < _ST_MAX_RECORDS_COUNT; rec_index++)
	{
		if (_segment_table->records[rec_index].is_loaded == true)
		{
			_unload_segment(_segment_table->records[rec_index].segment_ptr);
		}
	}
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
		printf("| %p\t| %c\t\t|\n", *(space + offset), space[offset] == NULL ? ' ' : *space[offset]);
	}

	printf(" -------------------------------\n");
}