#include "adress_spaces.h" 

#include <stdio.h>

int _init_pas(size_t size)
{
	if (size > _PAS_MAX_SIZE) {
		return _WRONG_PARAMS;
	}
	_pas_size = size;
	_first_free_pa_index = 0;

	_pas = (PA*)malloc(sizeof(PA) * size);
	for (unsigned int adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_pas[adress_index] = (PA)malloc(sizeof(PA));
	}

	if (_pas == NULL)
	{
		return _UNKNOWN_ERR;
	}

	return _SUCCESS;
}

int _init_vas (size_t size)
{
	if (size > _VAS_MAX_SIZE) {
		return _WRONG_PARAMS;
	}
	_vas_size = size;
	_first_free_va_index = 0;
	
	_vas = (VA*)malloc(sizeof(VA) * size);
	for (unsigned int adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		_vas[adress_index] = (VA)malloc(sizeof(VA));
	}

	if (_vas == NULL)
	{
		return _UNKNOWN_ERR;
	}

	return _SUCCESS;
}

PA _validate_pa (PA va)
{
	for (unsigned int adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		if (_pas[adress_index] == va) {
			return _pas[adress_index];
		}
	}

	return NULL;
}

VA _validate_va (VA va)
{
	for (unsigned int adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		if (_vas[adress_index] == va) {
			return _vas[adress_index];
		}
	}

	return NULL;
}

void _defragment_vas ()
{
	// do smth with _first_free_va_index
}

void _print_vas ()
{
	printf("Virtual adress space\n");
	printf("Index\tAdress\n");

	for (unsigned int adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		printf("%d\t%p", adress_index, _vas[adress_index]);
		printf("\n");
	}
}

void _print_pas ()
{
	printf("Physical adress space\n");
	printf("Index\tAdress\n");

	for (unsigned int adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		printf("%d\t%p", adress_index, _pas[adress_index]);
		printf("\n");
	}
}