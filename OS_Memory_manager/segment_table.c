#include "segment_table.h"

#include <string.h>
#include <stdio.h>

// Ёкземпл€р сегментной таблицы
segment_table _segment_table;

void _init_segment_table ()
{
	_segment_table.current_records_count = 0;
	_segment_table.first_free_index = 0;
}

void _print_segment_table ()
{
	printf("Index\tSegment VA\tSegment PA\tIs loaded\n");

	for (uint record_index = 0; record_index < _ST_MAX_RECORDS_COUNT; record_index++)
	{
		if (&_segment_table.records[record_index] == NULL)
		{
			printf("NULL");
		}
		else 
		{
			printf	("%d\t%p\t%p\t%d",
					record_index,
					_segment_table.records[record_index].segment_ptr,
					_segment_table.records[record_index].pa, 
					_segment_table.records[record_index].is_loaded
					);
		}

		printf("\n");
	}
}

segment_table_record* _add_record_to_segment_table (segment* segment)
{
	if (_segment_table.first_free_index >= _ST_MAX_RECORDS_COUNT)
	{
		return NULL;
	}

	segment_table_record* new_record_info = &_segment_table.records[_segment_table.first_free_index];
	new_record_info->segment_ptr = segment;
	new_record_info->pa = segment->starting_va; // TODO: преобразовать!!!
	new_record_info->is_loaded = false;

	_segment_table.first_free_index++;
	_segment_table.current_records_count++;

	return &_segment_table.records[_segment_table.first_free_index - 1];
}

void _remove_record_from_segment_table (unsigned int index)
{
	if (index >= _segment_table.current_records_count
		|| index < 0)
	{
		return;
	}

	// TODO: что насчет first_free_index? нужно все сместить к началу массива

	_segment_table.current_records_count--;

	_clear_segment_table_record(index);
}

void _clear_segment_table ()
{
	for (unsigned int record_index = 0; record_index < _segment_table.current_records_count; record_index++) {
		_clear_segment_table_record(record_index);
	}
}

void _clear_segment_table_record (unsigned int index)
{
	segment_table_record* record = &_segment_table.records[index];

	record->segment_ptr = NULL;
	record->pa = NULL;
	record->is_loaded = false;

	record = NULL;
}

segment* _find_segment (VA segment_starting_va)
{
	for (unsigned int record_index = 0; record_index < _segment_table.current_records_count; record_index++)
	{
		if (_segment_table.records[record_index].segment_ptr->starting_va == segment_starting_va)
		{
			return _segment_table.records[record_index].segment_ptr;
		}
	}

	return NULL;
}
