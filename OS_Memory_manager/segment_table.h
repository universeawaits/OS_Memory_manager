#include "adress_spaces.h"

#include <stdbool.h>

//	///////////////////////////////////////
//	va	- виртуальный адрес
//	vas - виртуальное адресное пространство
//
//	p	- физический
//	pa	- физический адрес
//	pas - физическое адресное пространство
//	///////////////////////////////////////

// Максимальное количество записей в таблице сегментов
#define _ST_MAX_RECORDS_COUNT 30
#define _NO_SEGMENT -1

// Тип, описывающий запись в таблице сегментов
typedef struct
{
	segment*	segment_ptr;
	bool		is_loaded;
}
st_record;

// Тип, описывающий таблицу сегментов
typedef struct
{
	size_t		current_records_count;
	uint		first_free_index;
	st_record*	records;
}
segment_table;

segment_table* _segment_table;	// Ссылка на экземпляр сегментной таблицы

int				_init_segment_table ();
int				_add_record_to_segment_table (segment* segment);
int				_remove_record_from_segment_table (segment* segment);
void			_clear_segment_table ();
void			_clear_segment_table_record (uint index);
segment*		_find_segment (VA segment_starting_va);
st_record*		_find_record (segment* segment);
void			_mark_as_unloaded (segment* segment);

void			_print_segment_table ();