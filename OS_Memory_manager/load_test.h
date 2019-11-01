#pragma once
#include "adress_spaces.h"

typedef struct {
	uint number_of_segs;
	char* graph_line;
} load_test_result;

void	init_load_testing_env ();
void	run_all_load_tests ();

void	iterate (uint iteration_number);
int		malloc_random (uint count_of_segs);
void	free_random (uint count_of_segs);


void	free_memory ();
void	init_iteration_result (uint count_of_columns, uint iteration_number);
void	sort_results (uint count_of_elements, load_test_result* arr);
void	print_results ();
