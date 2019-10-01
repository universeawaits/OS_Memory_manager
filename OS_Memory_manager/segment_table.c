#include "segment_table.h"

#include <string.h>
#include <stdlib.h >
#include <stdio.h>

// —сылка на экземпл€р сегментной таблицы
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
	_segment_table->records = (st_record*)malloc(sizeof(st_record) * _ST_MAX_RECORDS_COUNT);

	if (_segment_table->records == NULL)
	{
		return _UNKNOWN_ERR;
	}

	for (uint rec_index = 0; rec_index < _ST_MAX_RECORDS_COUNT; rec_index++)
	{
		_segment_table->records[rec_index].is_loaded = false;
		_segment_table->records[rec_index].pa = NULL;
		_segment_table->records[rec_index].segment_ptr = NULL;
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

	_segment_table->records[_segment_table->first_free_index].is_loaded = false;
	_segment_table->records[_segment_table->first_free_index].pa = segment->starting_va; // TODO: преобразовать!!!
	_segment_table->records[_segment_table->first_free_index].segment_ptr = segment;

	_segment_table->first_free_index++;
	_segment_table->current_records_count++;

	return _SUCCESS;
}

int _remove_record_from_segment_table (segment* segment)
{
	if (segment == NULL)
	{
		return _WRONG_PARAMS;
	}

	uint found_rec_index = 0;
	for (uint record_index = 0; record_index < _segment_table->current_records_count; record_index++) {
		if ((_segment_table->records + record_index)->segment_ptr == segment)
		{
			found_rec_index = record_index;
			break;
		}
	}

	_clear_segment_table_record(found_rec_index);

	uint last_rec_index = _segment_table->current_records_count - 1;
	_segment_table->records[found_rec_index] = _segment_table->records[last_rec_index];

	_clear_segment_table_record(last_rec_index);

	_segment_table->first_free_index--;
	_segment_table->current_records_count--;

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
