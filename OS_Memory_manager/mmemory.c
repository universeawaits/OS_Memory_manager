#include <stdlib.h>
#include "mmemory.h"

#define VIRTUAL_ADRESS_SPACE_SIZE 1024 * 1024;

typedef struct {
	VA virtualStartAdress;
	int size;
} Segment;

typedef struct {
	Segment segment;
	void* physicalAdress;
} SegmentTableRecord;

typedef struct {
	SegmentTableRecord* firstRecord;
	int size;
} SegmentTable;

#define SEGMENT_TABLE_RECORDS_COUNT_DEFAULT 1000;
#define SEGMENT_TABLE_SIZE_DEFAULT (sizeof(SegmentTableRecord) * SEGMENT_TABLE_RECORDS_COUNT_DEFAULT);