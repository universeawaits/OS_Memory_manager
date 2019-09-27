#include "adress_spaces.h" 

#include <stdio.h>

int _init_vas (size_t size)
{
	if (size > _VAS_MAX_SIZE) {
		return _WRONG_PARAMS;
	}
	_vas_size = size;
	_first_free_va_index = 0;

	return _SUCCESS;
}

int _init_pas (size_t size) 
{
	if (size > _PAS_MAX_SIZE) {
		return _WRONG_PARAMS;
	}
	_pas_size = size;
	_first_free_pa_index = 0;

	return _SUCCESS;
}

VA _validate_va (VA va)
{
	for (int adress_index = 0; adress_index < _vas_size; adress_index++)
	{
		if (_vas[adress_index] == va) {
			return _vas[adress_index];
		}
	}

	return NULL;
}

PA _validate_pa (PA va)
{
	for (int adress_index = 0; adress_index < _pas_size; adress_index++)
	{
		if (_pas[adress_index] == va) {
			return _pas[adress_index];
		}
	}

	return NULL;
}

VA _allocate_segment (size_t size)
{
	if (_first_free_va_index == _NULL_MEMORY_INDEX || 
		_first_free_va_index + size >= _VAS_MAX_SIZE)
	{
		_defragment_vas();

		if (_first_free_va_index == _NULL_MEMORY_INDEX ||
			_first_free_va_index + size >= _VAS_MAX_SIZE)
		{
			return NULL;
		}
	}

	VA starting_va = _vas[_first_free_va_index]; 
	_first_free_va_index += size;
	
	if (_first_free_va_index + size >= _VAS_MAX_SIZE) 
	{
		_first_free_va_index = _NULL_MEMORY_INDEX;
	}

	return starting_va;
}

void _defragment_vas ()
{

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