#include "mmemory.h"

/**
	v	- виртуальный
	va	- виртуальный адрес
	vas - виртуальное адресное пространство
	
	p	- физический
	pa	- физический адрес
	pas - физическое адресное пространство
	st	- таблица сегментов
**/

#ifndef ADRESS_SPACES_H
#define ADRESS_SPACES_H

// Сокращение для unsigned int (не size_t!)
typedef unsigned int uint;

// Тип, описывающий сегмент памяти
typedef struct
{
	VA		starting_va;
	VA		starting_pa;
	size_t	size;
}
segment;

// Минимальный размер физического адресного пространства (в байтах)
#define _PAS_MIN_SIZE (\
	sizeof(segment_table) + sizeof(st_record) * _ST_MAX_RECORDS_COUNT \
	)
#define _PAS_MAX_SIZE 100 * 1024			// Максимальный размер физического адресного пространства (в байтах)
#define _VAS_MAX_SIZE _PAS_MAX_SIZE		// Максимальный размер виртуального адресного пространства (в байтах)
#define _FORBIDDEN_ADRESS_OFFSET -1		// Адрес вне выделенного адресного пространсва
#define _VAS_NAME "Virtual adress space"
#define _PAS_NAME "Physical adress space"

VA*		_pas;							// Физическое адресное пространство
VA*		_vas;							// Виртуальное адресное пространство

size_t	_pas_size;						// Текущий размер физического адресного пространства
size_t	_vas_size;						// Текущий размер виртуального адресного пространства

VA*		_first_free_pa;					// Первый свободный физический адрес 
VA*		_first_free_va;					// Первый свободный виртуальный адрес 

VA*		_last_free_pa;					// Последний свободный физический адрес 
VA*		_last_free_va;					// Последний свободный виртуальный адрес 

/**
	@func	_init_pas
	@brief	Инициализация физического адресного пространства
**/
int		_init_pas (size_t size);

/**
	@func	_init_vas
	@brief	Инициализация виртуального адресного пространства
**/
int		_init_vas (size_t size);

/**
	@func	_init_adress
	@brief	Инициализация адреса, который будет
			являться начальным адресом сегмента
**/
int		_init_adress (VA* adress, size_t content_size);

/**
	@func	_adress_abs_offset
	@brief	Получение абсолютного смещения адреса
**/
uint	_adress_abs_offset(VA* space, VA adress);

/**
	@func	_clear_space_region
	@brief	Обнуление адресов на заданной области
**/
void	_clear_space_region (VA* starting_adress, size_t size);

/**
	@func	_first_null_content_adress
	@brief	Получение адреса первой свободной ячейки
**/
VA*		_first_null_content_adress (
		VA* space,
		VA* starting_adress,
		VA* last_free_space_adress
);

/**
	@func	_nulled_space_region_size
	@brief	Получение размера пустой области
**/
size_t	_nulled_space_region_size(VA* space, VA* space_region);

/**
	@func	_request_space_region_access
	@brief	Получение доступа к области памяти
**/
int		_request_space_region_access (VA va, VA* pa, size_t region_size);

/**
	@func	_request_free_space_region
	@brief	Получение пустой облатси заданного размера
**/
VA*		_request_free_space_region (
		VA* space,
		VA* last_free_space_adress,
		size_t size
);

/**
	@func	_organize_space_for_segment_allocation
	@brief	Поиск места или дефрагментация адресного пространства
**/
int		_organize_space_for_segment_allocation(
		VA* space,
		VA** first_free_space_adress,
		VA* last_free_space_adress,
		size_t segment_size
);

/**
	@func	_allocate_segment
	@brief	Размещение сегмента в адресном пространстве
**/
int	_allocate_segment(VA* allocationg_adress, size_t size);

/**
	@func	_register_segment
	@brief	Добавление информации о сегменте в
			сегментную таблицу
**/
int	_register_segment(segment* segment);

/**
	@func	_load_segment
	@brief	Загрузка сегмента в физическое адресное пространство
**/
int	_load_segment(segment* segment);

/**
	@func	_load_adjacent_segments
	@brief	Загрузка смежных сегментов
**/
int _load_adjacent_segments(segment* central_segment);

/**
	@func	_unload_segment
	@brief	Выгрузка сегмента из физического адресного пространства
**/
void _unload_segment(segment* segment);

/**
	@func	_unload_random_segment
	@brief	Выгрузка случайного сегмента
**/
void _unload_random_segment ();

/**
	@func	_unload_segments_to_free_space
	@brief	Выгрузка сегментов для освобождения места
**/
int _unload_segments_to_free_space (size_t space_region_size);

/**
	@func	_print_space
	@brief	Вывод содержимого адресного пространства
**/
void _print_space (
	VA* space,
	size_t adress_offset_limit,
	const char* space_name
);

#endif // !ADRESS_SPACES_H
