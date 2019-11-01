#include "mmemory.h"

void init_unit_testing_env();

void run_all_unit_tests();

void test_malloc__success();
void test_malloc__wrong_params();
void test_malloc__memory_lack();

void test_free__success();
void test_free_wrong_params();

void test_write__success();
void test_write__wrong_params();
void test_write__segment_access_violation();

void test_read__success();
void test_read__wrong_params();
void test_read__segment_access_violation();

void print_malloc_results();
void print_free_results();
void print_write_results();
void print_read_results();
