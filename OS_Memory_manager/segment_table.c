#include "segment_table.h"
#include "adress_spaces.h"

// Ёкземпл€р сегментной таблицы
segment_table* _segment_table;

void _init_segment_table () 
{
	segment_table segment_table_info;
	segment_table_info.current_records_count = 0;
	segment_table_info.first_free_index = 0;

	memcpy	(segment_table_info.records,
			(segment_table_record* [ST_MAX_RECORDS_COUNT]) { NULL }, 
			sizeof(segment_table_record*) * ST_MAX_RECORDS_COUNT
			);
	memcpy	(*_segment_table,
			segment_table_info,
			sizeof(segment_table)
			);
}

segment_table_record* _add_record_to_segment_table (segment* segment) 
{
	segment_table_record* new_record = NULL;

	segment_table_record new_record_info;
	new_record_info.segment = segment;
	new_record_info.pa = segment->starting_va; // TODO: преобразовать!!!
	new_record_info.is_in_pMemory = false;

	new_record = memcpy	(new_record,
						new_record_info, 
						sizeof(segment_table_record)
						);

	_segment_table->records[_segment_table->first_free_index] = new_record;
	_segment_table->first_free_index++;
	_segment_table->current_records_count++;
}

void _clear_segment_table () 
{
	for (int record_index = 0; record_index < _segment_table->current_records_count; record_index++) {
		_clear_segment_table_record(record_index);
	}
}

void _clear_segment_table_record (size_t index) 
{
	segment_table_record* record = &(_segment_table->records[index]);

	record->segment = NULL;
	record->pa = NULL;
	record->is_in_pMemory = false;

	record = NULL;
}
