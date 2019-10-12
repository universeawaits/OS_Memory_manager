#include "mmemory.h"

int n;
int szPage;

VA* out_ptr;
size_t size;

VA** freed_seg_starting_adress;

void init_testing_env ();

void test_init__success ();
void test_init__wrong_params ();
void test_init__unknown_err ();

void test_malloc__success ();
void test_malloc__wrong_params ();
void test_malloc__memory_lack ();
void test_malloc__unknown_err ();

void test_free__success();
void test_free__wrong_params();
void test_free__unknown_err();