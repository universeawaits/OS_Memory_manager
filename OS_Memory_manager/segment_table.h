#include "mmemory.h"
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
#define _ST_MAX_RECORDS_COUNT (_VAS_MAX_SIZE / sizeof(segment_table_record))

// Тип, описывающий сегмент памяти
typedef struct {
	VA		starting_va;
	size_t	size;
} segment;

// Тип, описывающий запись в таблице сегментов
typedef struct {
	segment*	segment_ptr;
	PA			pa;
	bool		is_loaded;
} segment_table_record;

// Тип, описывающий таблицу сегментов
typedef struct {
	size_t					current_records_count;
	unsigned int			first_free_index;
	segment_table_record	records[_ST_MAX_RECORDS_COUNT];
} segment_table;

void					_init_segment_table ();
segment_table_record*	_add_record_to_segment_table (segment* segment);
void					_remove_record_from_segment_table (unsigned int index);
void					_clear_segment_table ();
void					_clear_segment_table_record (unsigned int index);
segment*				_find_segment (VA segment_starting_va);

void					_print_segment_table ();
