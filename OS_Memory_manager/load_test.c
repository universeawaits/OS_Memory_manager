#include "load_test.h"
#include "adress_spaces.h"
#include "segment_table.h"
#include "mmemory.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

const uint count_of_iterations = 100;

const uint _init_n = 100;
const size_t _init_szPage = 1000;

const uint min_seg_count = 5;
const uint max_seg_count = 100;

VA* allocated_ptr;

uint delta_time = 0;

load_test_result* results;

void init_load_testing_env ()
{
	allocated_ptr = (VA*)malloc(sizeof(VA));
	results = (load_test_result*)malloc(
		sizeof(load_test_result) * count_of_iterations
	);
}

void run_all_load_tests() 
{
	printf("\n\n");
	srand(time(NULL));
	for (uint i = 0; i < count_of_iterations; i++)
	{
		iterate(i);
	}
	sort_results(count_of_iterations, results);
	print_results();
}

void iterate(uint iteration_number)
{
	uint n = min_seg_count + rand() % max_seg_count;

	free_memory();
	_init(_init_n, _init_szPage);

	while (malloc_random(n / 2) != _MEMORY_LACK)
	{
		free_random(n / 10);
	}

	init_iteration_result(n, iteration_number);
	delta_time = 0;
}

int malloc_random(uint count_of_segs)
{
	for (uint i = 0; i < count_of_segs; i++)
	{
		if (_malloc(
			allocated_ptr,
			1 + rand() % (_vas_size / count_of_segs)
			) == _MEMORY_LACK)
		{
			return _MEMORY_LACK;
		}
		delta_time++;
	}

	return _SUCCESS;
}

void free_random (uint count_of_segs)
{
	for (uint i = 0; i < count_of_segs; i++)
	{
		_free(_segment_table->records[i].segment_ptr->starting_va);
		delta_time++;
	}
}


void free_memory ()
{
	size_t records_count = _segment_table->current_records_count;
	for (int i = records_count - 1; i >= 0; i--)
	{
		free(_segment_table->records[i].segment_ptr->starting_va);
		_free(_segment_table->records[i].segment_ptr->starting_va);
	}
}

void init_iteration_result (uint n, uint iteration_number)
{
	char* line = (char*)malloc(sizeof(char) * delta_time / 2);
	uint i = 0;
	for (i = 0; i < delta_time / 2; i++)
	{
		*(line + i) = '=';
	}
	*(line + i) = '\0';

	results[iteration_number].graph_line = line;
	results[iteration_number].number_of_segs = n;
}

void print_results ()
{
	for (int i = 0; i < count_of_iterations; i++)
	{
		printf("\n%d\t%s", results[i].number_of_segs, results[i].graph_line);
	}
}

void sort_results(int count_of_elements, load_test_result* arr)
{
	int i, j;
	load_test_result t;

	for (i = 0; i < count_of_elements; i++) {

		for (j = i + 1; j < count_of_elements; j++) {

			if ((arr + j)->number_of_segs < (arr + i)->number_of_segs) {

				t = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = t;
			}
		}
	}
}