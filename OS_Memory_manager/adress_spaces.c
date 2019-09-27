#include "adress_spaces.h" 

#include <stdio.h>

VA _init_vas (size_t size)
{
	if (size > VAS_MAX_SIZE) {
		return NULL;
	}
	_vas_size = size;
	_first_free_va_index = 0;

	VA va = "hahahaahahah";

	for (unsigned int adress_index = 0; adress_index < size; adress_index++) 
	{
		_vas[adress_index] = va;
	}

	for (unsigned int adress_index = size; adress_index < VAS_MAX_SIZE; adress_index++)
	{
		_vas[adress_index] = NULL;
	}

	return _vas[_first_free_va_index];
}

PA _init_pas (size_t size) 
{
	if (size > PAS_MAX_SIZE) {
		return NULL;
	}
	_pas_size = size;
	_first_free_pa_index = 0;

	PA pa = "dsffs";

	for (unsigned int adress_index = 0; adress_index < size; adress_index++)
	{
		_pas[adress_index] = pa;
	}

	for (unsigned int adress_index = size; adress_index < PAS_MAX_SIZE; adress_index++)
	{
		_pas[adress_index] = NULL;
	}

	return _pas[_first_free_pa_index];
}

VA _allocate_segment (size_t size)
{
	if (_first_free_va_index == NULL_MEMORY_INDEX || 
		_first_free_va_index + size >= VAS_MAX_SIZE)
	{
		_defragment_vas();

		if (_first_free_va_index == NULL_MEMORY_INDEX ||
			_first_free_va_index + size >= VAS_MAX_SIZE)
		{
			return NULL;
		}
	}

	VA starting_va = _vas[_first_free_va_index]; 
	_first_free_va_index += size;
	
	if (_first_free_va_index + size >= VAS_MAX_SIZE) 
	{
		_first_free_va_index = NULL_MEMORY_INDEX;
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