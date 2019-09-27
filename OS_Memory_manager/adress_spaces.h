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

#define PAS_MAX_SIZE 1024			// Максимальный размер физического адресного пространства (в байтах)
#define VAS_MAX_SIZE PAS_MAX_SIZE	// Максимальный размер виртуального адресного пространства (в байтах)
#define NULL_MEMORY_INDEX -1		// Индекс ячейки, которая находится вне памяти

PA _pas[PAS_MAX_SIZE];				// Физическое адресное пространство
VA _vas[VAS_MAX_SIZE];				// Виртуальное адресное пространство

size_t _pas_size;
size_t _vas_size;

int _first_free_va_index;
int _first_free_pa_index;

VA		_init_vas (size_t size);
PA		_init_pas (size_t size);
VA		_allocate_segment (size_t size);
void	_defragment_vas ();

void _print_vas ();
void _print_pas ();