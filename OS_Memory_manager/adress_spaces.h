#include "mmemory.h"

//	///////////////////////////////////////
//	va	- виртуальный адрес
//	vas - виртуальное адресное пространство
//
//	p	- физический
//	pa	- физический адрес
//	pas - физическое адресное пространство
//	///////////////////////////////////////

typedef char* PA;					// Тип, описывающий физический адрес

#define _PAS_MAX_SIZE 1024			// Максимальный размер физического адресного пространства (в байтах)
#define _VAS_MAX_SIZE _PAS_MAX_SIZE	// Максимальный размер виртуального адресного пространства (в байтах)
#define _NULL_MEMORY_INDEX -1		// Индекс ячейки, которая находится вне памяти

PA _pas[_PAS_MAX_SIZE];				// Физическое адресное пространство
VA _vas[_VAS_MAX_SIZE];				// Виртуальное адресное пространство

size_t _pas_size;
size_t _vas_size;

int _first_free_va_index;
int _first_free_pa_index;

int		_init_vas (size_t size);
int		_init_pas (size_t size);
VA		_validate_va (VA va);
PA		_validate_pa (PA va);
VA		_allocate_segment (size_t size);
void	_defragment_vas ();

void	_print_vas ();
void	_print_pas ();