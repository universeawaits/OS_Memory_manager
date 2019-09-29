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

// “ип, описывающий физический адрес
typedef char* PA;
// —окращение дл€ unsigned int (не size_t!)
typedef unsigned int uint;

// “ип, описывающий сегмент пам€ти
typedef struct
{
	VA		starting_va;
	size_t	size;
}
segment;

#define _PAS_MAX_SIZE 1024				// ћаксимальный размер физического адресного пространства (в байтах)
#define _VAS_MAX_SIZE _PAS_MAX_SIZE		// ћаксимальный размер виртуального адресного пространства (в байтах)

PA*			_pas;						// ‘изическое адресное пространство
VA*			_vas;						// ¬иртуальное адресное пространство

size_t		_pas_size;					// “екущий размер физического адресного пространства
size_t		_vas_size;					// “екущий размер виртуального адресного пространства

PA			_first_free_pa;
VA			_first_free_va;

PA			_last_free_pa;
VA			_last_free_va;

int				_init_pas(size_t size);
int				_init_vas(size_t size);
uint			_validate_pa(PA va);
uint			_validate_va(VA va);
segment*		_find_segment(VA starting_va);
void			_defragment_vas();

void			_print_vas();
void			_print_pas();


#endif // !ADRESS_SPACES_H

