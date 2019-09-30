#include "mmemory.h"

//#define __TEST_INIT_N				10
//#define __TEST_INIT_SZBLOCK			10
//
//#define __TEST_MALLOC_SIZE_SMALL	10
//#define __TEST_MALLOC_SIZE_MEDIUM	200
//#define __TEST_MALLOC_SIZE_LARGE	700
//
//#define __TEST_READ_PBUFFER_SMALL	10
//#define __TEST_READ_PBUFFER_MEDIUM	200
//#define __TEST_READ_PBUFFER_LARGE	700

void test_init (int n, int szPage);
void test_malloc (VA* out_ptr, size_t size);
void test_free (VA segment_starting_va);
void test_read (VA ptr, void* pBuffer, size_t szBuffer);
void test_write (VA ptr, void* pBuffer, size_t szBuffer);