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

#define ST_MAX_RECORDS_COUNT (VAS_MAX_SIZE / sizeof(segment_table_record))

typedef struct {
	VA		starting_va;
	size_t	size;
} segment; // Тип, описывающий сегмент

typedef struct {
	segment*	segment;
	PA			pa;
	bool		is_in_pMemory;
} segment_table_record; // Тип, описывающий запись в таблице сегментов

typedef struct {
	size_t					current_records_count;
	size_t					first_free_index;
	segment_table_record*	records[];
} segment_table; // Тип, описывающий таблицу сегментов

void					_init_segment_table ();
segment_table_record*	_add_record_to_segment_table(segment* segment);
void					_clear_segment_table_record (size_t index);