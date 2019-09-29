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
	VA pas_content = (PA)malloc(sizeof(char) * size);

	if (pas_content == NULL)
	{
		return _UNKNOWN_ERR;
	}

	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_pas[adress_index] = pas_content + adress_index;
	}
	_first_free_pa = _pas[0];
	_last_free_pa = _pas[_pas_size - 1];

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
	VA vas_content = (VA)malloc(sizeof(char) * size);

	if (vas_content == NULL)
	{
		return _UNKNOWN_ERR;
	}

	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		_vas[adress_index] = vas_content + adress_index;
	}
	_first_free_va = _vas[0];
	_last_free_va = _vas[_vas_size - 1];

	return _SUCCESS;
}

unsigned int _validate_pa (PA va)
{
	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		if (_pas[adress_index] == va) {
			return adress_index;
		}
	}
	
	return NULL;
}

unsigned int _validate_va (VA va)
{
	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		if (_vas[adress_index] == va) {
			return adress_index;
		}
	}

	return NULL;
}

void _defragment_vas ()
{
	// do smth with _first_free_va
}

void _print_vas ()
{
	printf("Virtual adress space\n");
	printf("Index\tAdress\n");

	for (uint adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		printf("%d\t%p", adress_index, _vas[adress_index]);
		printf("\n");
	}
}

void _print_pas ()
{
	printf("Physical adress space\n");
	printf("Index\tAdress\n");

	for (uint adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		printf("%d\t%p", adress_index, _pas[adress_index]);
		printf("\n");
	}
}