#include "mmemory.h"

void test_init (int n, int szPage);
void test_malloc (VA* out_ptr, size_t size);
void test_free (VA segment_starting_va);
void test_read (VA ptr, void* pBuffer, size_t szBuffer);
void test_write (VA ptr, void* pBuffer, size_t szBuffer);