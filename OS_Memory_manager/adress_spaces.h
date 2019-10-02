#include "mmemory.h"

//	///////////////////////////////////////
//	va	- виртуальный адрес
//	vas - виртуальное адресное пространство
//
//	p	- физический
//	pa	- физический адрес
//	pas - физическое адресное пространство
//	st	- таблица сегментов
//	///////////////////////////////////////

#ifndef ADRESS_SPACES_H
#define ADRESS_SPACES_H

// Тип, описывающий физический адрес
typedef char* PA;
// Сокращение для unsigned int (не size_t!)
typedef unsigned int uint;

// Тип, описывающий сегмент памяти
typedef struct
{
	VA		starting_va;
	size_t	size;
}
segment;

#define _PAS_MAX_SIZE 1024				// Максимальный размер физического адресного пространства (в байтах)
#define _VAS_MAX_SIZE _PAS_MAX_SIZE		// Максимальный размер виртуального адресного пространства (в байтах)
#define _FORBIDDEN_ADRESS_OFFSET -1		// Адрес вне выделенного адресного пространсва

PA*			_pas;						// Физическое адресное пространство
VA*			_vas;						// Виртуальное адресное пространство

size_t		_pas_size;					// Текущий размер физического адресного пространства
size_t		_vas_size;					// Текущий размер виртуального адресного пространства

PA*			_first_free_pa;				// Первый свободный физический адрес 
VA*			_first_free_va;				// Первый свободный виртуальный адрес 

PA*			_last_free_pa;				// Последний свободный физический адрес 
VA*			_last_free_va;				// Последний свободный виртуальный адрес 

int			_init_pas (size_t size);
int			_init_vas (size_t size);
uint		_validate_pa (PA va);
uint		_validate_va (VA va);
segment*	_find_segment (VA starting_va);
VA*			_request_free_space (size_t size);
void		_defragment_vas ();
size_t		_nulled_space_size (VA* starting_adress);
VA*			_first_adress_with_null_content (VA* starting_adress);
void		_shift_vas_content_to_left (VA* starting_adress, uint offset);

void		_print_vas();
void		_print_pas();


#endif // !ADRESS_SPACES_H

