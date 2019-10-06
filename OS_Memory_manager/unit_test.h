#include "mmemory.h"

int n;
int szPage;

VA* out_ptr;
size_t size;

VA segment_starting_adress;

void test_init (int n, int szPage);
void test_malloc (VA* out_ptr, size_t size);

void test_init__success ();
void test_init__wrong_params ();
void test_init__unknown_err ();

void test_malloc__success ();
void test_malloc__wrong_params ();
void test_malloc__memory_lack ();
void test_malloc__unknown_err ();