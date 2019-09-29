#include "segment_table.h"

#include <string.h>
#include <stdlib.h >
#include <stdio.h>

// ������ �� ��������� ���������� �������
segment_table* _segment_table;

int _init_segment_table ()
{
	_segment_table = (segment_table*)malloc(sizeof(segment_table));

	if (_segment_table == NULL)
	{
		return _UNKNOWN_ERR;
	}
	_segment_table->current_records_count = 0;
	_segment_table->first_free_index = 0;
	_segment_table->records = (st_record*)malloc(sizeof(st_record));

	if (_segment_table->records == NULL)
	{
		return _UNKNOWN_ERR;
	}

	return _SUCCESS;
}

void _print_segment_table ()
{
	printf("Index\tSegment VA\tSegment PA\tIs loaded\n");

	for (uint record_index = 0; record_index < _ST_MAX_RECORDS_COUNT; record_index++)
	{
		if (_segment_table->records + record_index == NULL)
		{
			continue;
		}
		else 
		{
			printf	("%d\t%p\t%p\t%d",
					record_index,
					_segment_table->records[record_index].segment_ptr,
					_segment_table->records[record_index].pa,
					_segment_table->records[record_index].is_loaded
					);
		}

		printf("\n");
	}
}

int _add_record_to_segment_table (segment* segment)
{
	if (_segment_table->first_free_index >= _ST_MAX_RECORDS_COUNT)
	{
		return _MEMORY_LACK;
	}

	st_record* new_record = (st_record*)malloc(sizeof(st_record));
	
	if (new_record == NULL)
	{
		return _UNKNOWN_ERR;
	}
	new_record->segment_ptr = segment;
	new_record->pa			= segment->starting_va; // TODO: �������������!!!
	new_record->is_loaded	= false;

	_segment_table->first_free_index++;
	_segment_table->current_records_count++;

	return _SUCCESS;
}

int _remove_record_from_segment_table (uint index)
{
	if (index >= _ST_MAX_RECORDS_COUNT
		|| index < 0)
	{
		return _WRONG_PARAMS;
	}

	// TODO: ��� ������ first_free_index? ����� ��� �������� � ������ �������

	_segment_table->current_records_count--;

	_clear_segment_table_record(index);

	return _SUCCESS;
}

void _clear_segment_table ()
{
	for (uint record_index = 0; record_index < _segment_table->current_records_count; record_index++) {
		_clear_segment_table_record(record_index);
	}
}

void _clear_segment_table_record (uint index)
{
	st_record* record = _segment_table->records + index;

	record->segment_ptr = NULL;
	record->pa			= NULL;
	record->is_loaded	= false;

	record = NULL;
}

segment* _find_segment (VA segment_starting_va)
{
	for (uint record_index = 0; record_index < _segment_table->current_records_count; record_index++)
	{
		if (_segment_table->records[record_index].segment_ptr->starting_va == segment_starting_va)
		{
			return _segment_table->records[record_index].segment_ptr;
		}
	}

	return NULL;
}
