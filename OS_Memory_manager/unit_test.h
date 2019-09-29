#include "mmemory.h"

int test_init(size_t vas_size);
int test_malloc(VA* out_ptr, size_t size);
int test_free(VA segment_starting_va);
int test_read(VA ptr, void* pBuffer, size_t szBuffer);
int test_write(VA ptr, void* pBuffer, size_t szBuffer);