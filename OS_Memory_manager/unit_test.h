#include "mmemory.h"

//int n;
//int szPage;
//
//VA* out_ptr;
//size_t size;
//
//VA** freed_seg_starting_adress;
//
//VA* written;
//VA* read;
//VA pBuffer;

//void init_testing_env ();
//
//void test_init__success ();
//void test_init__wrong_params ();
//void test_init__unknown_err ();
//
//void test_malloc__success ();
//void test_malloc__wrong_params ();
//void test_malloc__memory_lack ();
//void test_malloc__unknown_err ();
//
//void test_free__success();
//void test_free__wrong_params();
//void test_free__unknown_err();
//
//void test_write__success();
//void test_write__wrong_params();
//void test_write__unknown_error();
//void test_write__segment_access_violation();
//
//void test_read__success();
//void test_read__wrong_params();
//void test_read__unknown_error();
//void test_read__segment_access_violation();

void init_testing_env();

void run_all_tests();

void test_malloc__success();
void test_malloc__wrong_params();
void test_malloc__memory_lack();

void test_free__success();
void test_free_wrong_params();

void test_write__sucess();
void test_write__wrong_params();
void test_write__segment_access_violation();

void test_read__sucess();
void test_read__wrong_params();
void test_read__segment_access_violation();
