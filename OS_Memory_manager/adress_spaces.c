#include "adress_spaces.h" 

#include <stdio.h>
#include <stdlib.h>

int _init_pas(size_t size)
{
	if (size > _PAS_MAX_SIZE || size < 0) {
		return _WRONG_PARAMS;
	}

	_pas = (PA*)malloc(sizeof(PA) * size);

	if (_pas == NULL)
	{
		return _UNKNOWN_ERR;
	}
	_pas_size = size;

	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_pas[adress_index] = NULL;
	}
	_first_free_pa = _pas;
	_last_free_pa = _pas + _pas_size;

	return _SUCCESS;
}

int _init_vas (size_t size)
{
	if (size > _VAS_MAX_SIZE || size < 0) {
		return _WRONG_PARAMS;
	}
	
	_vas = (VA*)malloc(sizeof(VA) * size);

	if (_vas == NULL)
	{
		return _UNKNOWN_ERR;
	}
	_vas_size = size;

	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		_vas[adress_index] = NULL;
	}
	_first_free_va = _vas;
	_last_free_va = _vas + _vas_size;

	return _SUCCESS;
}

uint _validate_pa (PA va)
{
	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		if (_pas[adress_index] == va) {
			return adress_index;
		}
	}
	
	return _FORBIDDEN_ADRESS;
}

uint _validate_va (VA va)
{
	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		if (_vas[adress_index] == va) {
			return adress_index;
		}
	}

	return _FORBIDDEN_ADRESS;
}

void _defragment_vas ()
{
	// do smth with _first_free_va
}

void _print_vas ()
{
	printf("Virtual adress space\n");
	printf("Adress\Content\t\n");

	for (uint adress_offset = 0; adress_offset < _vas_size; adress_offset++)
	{
		printf("%p\t%c\n", _vas + adress_offset, _vas[adress_offset] == NULL ? ' ' : *_vas[adress_offset]);
	}
}

void _print_pas ()
{
	printf("Physical adress space\n");
	printf("Adress\t\tContent\n");

	for (uint adress_offset = 0; adress_offset < _pas_size; adress_offset++)
	{
		printf("%p\t%c\n", _pas + adress_offset, _pas[adress_offset] == NULL ? ' ' : *_pas[adress_offset]);
	}
}
